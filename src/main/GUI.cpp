#include "main/GUI.hpp"
#include "IGUIButton.h"
#include "IGUIComboBox.h"
#include "IGUIStaticText.h"
#include "main/CameraManager.hpp"
#include "main/EventReciever.hpp"
#include "main/Macros.hpp"
#include "main/Orbit.hpp"

#include <cmath>
#include <iostream>
#include <irrlicht.h>
#include <map>
#include <memory>
#include <string>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

void GUI::run() {
  // runs constructor

  GUI gui = GUI();

  gui.openTitleScreen();

  // adds some misc utility variables

  ITimer *timer = gui.device->getTimer();
  double lastTime = timer->getTime();

  // forever loop that updates positions of planets and then draws planets

  while (gui.device->run()) {

    gui.driver->beginScene(true, true, SColor(255, 10, 10, 10));

    if (gui.titleScreenOpen) {
      gui.handleTitleScreenButtons();
    } else {

      gui.pm.updatePositions((timer->getTime() - lastTime) / 1000);
      gui.pm.drawPlanets(gui.driver);

      gui.handleMouseInput();
      gui.handleButtonPresses();
      gui.camera->updatePosition();

      if (gui.receiver->getPlanetMenuState()) {
        gui.updatePlanetInMenu();
      }

      gui.smgr->drawAll();
    }

    gui.guienv->drawAll();

    gui.driver->endScene();

    lastTime = timer->getTime();
    gui.receiver->update();
  }

  gui.pm.removeAll();

  gui.device->drop();
}

GUI::GUI() {
  device = createDevice(video::EDT_OPENGL,
                        dimension2d<u32>(SCREEN_WIDTH, SCREEN_HEIGHT), 16, true,
                        false, false, 0);

  if (!device) {
    std::cerr << "no device\n";
  }

  device->setWindowCaption(L"Orbit Simulator");

  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  guienv = device->getGUIEnvironment();

  colmgr = smgr->getSceneCollisionManager();

  if (!driver || !smgr || !guienv) {
    std::cerr << "problem with initialisation\n";
  }

  pm = PlanetManager();
  camera = std::make_unique<CameraManager>(smgr);

  receiver = std::make_unique<EventReceiver>();
  device->setEventReceiver(receiver.get());
}

void GUI::createTopBar() {

  topBar = guienv->addStaticText(
      L"", rect<s32>(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 10), true, true);

  topBar->setDrawBackground(true);
  topBar->setBackgroundColor(video::SColor(255, 50, 50, 50));

  pauseButton = guienv->addButton(rect<s32>(1100, 25, 1150, 75), topBar);
  pauseButton->setImage(driver->getTexture("assets/buttons/pause.png"));
  pauseButton->setScaleImage();

  normalSpeedButton = guienv->addButton(rect<s32>(1170, 25, 1220, 75), topBar);
  normalSpeedButton->setImage(driver->getTexture("assets/buttons/normal.png"));
  normalSpeedButton->setScaleImage();

  fastSpeedButton = guienv->addButton(rect<s32>(1240, 25, 1290, 75), topBar);
  fastSpeedButton->setImage(driver->getTexture("assets/buttons/fast.png"));
  fastSpeedButton->setScaleImage();

  veryFastButton = guienv->addButton(rect<s32>(1310, 25, 1360, 75), topBar);
  veryFastButton->setImage(driver->getTexture("assets/buttons/veryfast.png"));
  veryFastButton->setScaleImage();

  extremelyFastButton =
      guienv->addButton(rect<s32>(1380, 25, 1430, 75), topBar);
  extremelyFastButton->setImage(
      driver->getTexture("assets/buttons/extremelyfast.png"));
  extremelyFastButton->setScaleImage();

  resetButton = guienv->addButton(rect<s32>(300, 25, 350, 75), topBar);
  resetButton->setImage(driver->getTexture("assets/buttons/reset.jpg"));
  resetButton->setScaleImage();

  addPlanetButton = guienv->addButton(rect<s32>(600, 25, 650, 75), topBar);
  addPlanetButton->setImage(driver->getTexture("assets/buttons/add.jpg"));
  addPlanetButton->setScaleImage();
}

void GUI::handleButtonPresses() {

  if (pauseButton->isPressed()) {
    pm.setTimeSpeed(0);
  }
  if (normalSpeedButton->isPressed()) {
    pm.setTimeSpeed(1);
  }
  if (fastSpeedButton->isPressed()) {
    pm.setTimeSpeed(2);
  }
  if (veryFastButton->isPressed()) {
    pm.setTimeSpeed(4);
  }
  if (extremelyFastButton->isPressed()) {
    pm.setTimeSpeed(8);
  }

  if (resetButton->isPressed()) {

    // delete all simulation data
    pm.removeAll();
    pm.setTimeSpeed(1);
    camera->reset();
    scenePointerMap.clear();

    // re-add planets from start of simulation

    switch (startType) {
    case _Normal:

      addStartingPlanets();
      break;
    case _Empty:
      break;
    case _Binary:
      void createBinarySystem();
      break;
    }
  }

  if (addPlanetButton->isPressed()) {
    if (!openPopUpFlag) {
      openPopUpFlag = true;
      createAddPlanetPopUp();
    }
  } else {
    openPopUpFlag = false;
  }

  if (receiver->getPlanetWindowState()) {
    if (createPlanetButton->isPressed()) {

      if (createPlanetFromInput()) {

        addPlanetWindow->remove();
        receiver->setPlanetWindowSate(false);
      }
    }
  }
}

void GUI::addStartingPlanets() {

  addPlanet(Vector(0, 0, 0), Vector(0, 0, 0), _Star);

  // 1825
  addPlanet(Vector(0, 0, 3000), Vector(1825, 0, 0), _Telluric);
  addPlanet(Vector(0, 0, 6000), Vector(1290, 0, 0), _Telluric);
  addPlanet(Vector(0, 0, 6050), Vector(1401, 0, 0), _Comet);
  addPlanet(Vector(0, 0, 10000), Vector(1000, 0, 0), _Gas);
  addPlanet(Vector(0, 0, 10250), Vector(1200, 0, 0), _Telluric);
  addPlanet(Vector(0, 0, 15000), Vector(816, 0, 0), _Ringed);
  addPlanet(Vector(0, 0, 30000), Vector(577, 0, 0), _Telluric);
}

void GUI::addPlanet(const Vector &_position, const Vector &_velocity,
                    int type) {

  std::weak_ptr<ISceneNode> temp =
      pm.addPlanet(_position, _velocity, smgr, driver, type);

  scenePointerMap.insert({temp.lock().get(), temp});
}

void GUI::handleMouseInput() {

  ISceneNode *selected = nullptr;
  std::string empty = "";

  if (receiver->GetMouseState().leftButtonDown) {
    camera->updateAngles(receiver->GetMouseState().Position);
  } else {
    camera->resetDelta();
  }

  camera->updateRadius(receiver->GetMouseState().wheel);

  // handle selection of planet
  if (receiver->GetMouseState().shouldSelectPlanet) {

    mousepos = receiver->GetMouseState().Position;
    selected = colmgr->getSceneNodeFromScreenCoordinatesBB(
        vector2d(mousepos.X, mousepos.Y));

    if (selected) { // check that it's not nullptr

      if (empty.compare(selected->getName())) { // check is name is not empty
                                                // - if name is empty then we
                                                // are looking at nothing
        camera->setSelectedPlanet(scenePointerMap[selected]);
      }
    }
  }

  // handle opening planet menu
  if (receiver->GetMouseState().rightButtonDown) {

    if (!rightClicking) {

      mousepos = receiver->GetMouseState().Position;
      selected = colmgr->getSceneNodeFromScreenCoordinatesBB(
          vector2d(mousepos.X, mousepos.Y));

      if (selected) { // check that it's not nullptr

        if (empty.compare(selected->getName())) { // check is name is not empty
                                                  // - if name is empty then we
                                                  // are clicking on nothing
          // todo, make popup from this planet
          createPlanetMenu(
              pm.getPlanetFromSceneNode(scenePointerMap[selected]));
        }
      }
    }
    rightClicking = true;
  } else {
    rightClicking = false;
  }
}

void GUI::createAddPlanetPopUp() {

  addPlanetWindow = guienv->addWindow(rect<s32>(600, 200, 1100, 800), true,
                                      L"Add Planet", nullptr, _AddPlanet);
  addPlanetWindow->setDrawBackground(true);
  // width = 500, height = 600

  int x = 70;
  int y = 55;

  IGUIImage *starImage =
      guienv->addImage(rect<s32>(x, y, x + 90, y + 90), addPlanetWindow);
  starImage->setImage(driver->getTexture("assets/planetIcons/star.png"));
  starImage->setScaleImage(true);

  x += 135;

  IGUIImage *ringedImage =
      guienv->addImage(rect<s32>(x, y, x + 90, y + 90), addPlanetWindow);
  ringedImage->setImage(driver->getTexture("assets/planetIcons/ringed.png"));
  ringedImage->setScaleImage(true);

  x += 135;

  IGUIImage *gasImage =
      guienv->addImage(rect<s32>(x, y, x + 90, y + 90), addPlanetWindow);
  gasImage->setImage(driver->getTexture("assets/planetIcons/gas.png"));
  gasImage->setScaleImage(true);

  x = 70;
  y += 110;

  IGUIImage *telluricImage =
      guienv->addImage(rect<s32>(x, y, x + 90, y + 90), addPlanetWindow);
  telluricImage->setImage(
      driver->getTexture("assets/planetIcons/telluric.png"));
  telluricImage->setScaleImage(true);

  x += 135;

  IGUIImage *asteroidImage =
      guienv->addImage(rect<s32>(x, y, x + 90, y + 90), addPlanetWindow);
  asteroidImage->setImage(
      driver->getTexture("assets/planetIcons/asteroid.png"));
  asteroidImage->setScaleImage(true);

  x += 135;

  IGUIImage *cometImage =
      guienv->addImage(rect<s32>(x, y, x + 90, y + 90), addPlanetWindow);
  cometImage->setImage(driver->getTexture("assets/planetIcons/comet.png"));
  cometImage->setScaleImage(true);

  planetSelect =
      guienv->addComboBox(rect<s32>(180, 280, 320, 310), addPlanetWindow);

  planetSelect->addItem(L"Asteroid");
  planetSelect->addItem(L"Comet");
  planetSelect->addItem(L"Gas");
  planetSelect->addItem(L"Ringed");
  planetSelect->addItem(L"Star");
  planetSelect->addItem(L"Telluric");

  inputTypeSelect =
      guienv->addComboBox(rect<s32>(25, 280, 150, 310), addPlanetWindow);

  inputTypeSelect->addItem(L"Position and Velocity Input");
  inputTypeSelect->addItem(L"Orbital Characteristics Input");

  x = 50;
  y = 350;

  // add position edit boxes

  guienv->addStaticText(L"Position", rect<s32>(x, y, x + 60, y + 15), false,
                        false, addPlanetWindow);
  x += 64;
  guienv->addStaticText(L"X:", rect<s32>(x, y, x + 20, y + 15), false, false,
                        addPlanetWindow);
  x += 32;
  xPosEditBox = guienv->addEditBox(L"", rect<s32>(x, y, x + 64, y + 15), true,
                                   addPlanetWindow);
  x += 88;
  guienv->addStaticText(L"Y:", rect<s32>(x, y, x + 20, y + 15), false, false,
                        addPlanetWindow);
  x += 32;
  yPosEditBox = guienv->addEditBox(L"", rect<s32>(x, y, x + 64, y + 15), true,
                                   addPlanetWindow);
  x += 88;
  guienv->addStaticText(L"Z:", rect<s32>(x, y, x + 20, y + 15), false, false,
                        addPlanetWindow);
  x += 32;
  zPosEditBox = guienv->addEditBox(L"", rect<s32>(x, y, x + 64, y + 15), true,
                                   addPlanetWindow);
  x = 50;
  y += 30;

  // add velocity edit boxes

  guienv->addStaticText(L"Velocity", rect<s32>(x, y, x + 60, y + 15), false,
                        false, addPlanetWindow);
  x += 64;
  guienv->addStaticText(L"X:", rect<s32>(x, y, x + 20, y + 15), false, false,
                        addPlanetWindow);
  x += 32;
  xVelEditBox = guienv->addEditBox(L"", rect<s32>(x, y, x + 64, y + 15), true,
                                   addPlanetWindow);
  x += 88;
  guienv->addStaticText(L"Y:", rect<s32>(x, y, x + 20, y + 15), false, false,
                        addPlanetWindow);
  x += 32;
  yVelEditBox = guienv->addEditBox(L"", rect<s32>(x, y, x + 64, y + 15), true,
                                   addPlanetWindow);
  x += 88;
  guienv->addStaticText(L"Z:", rect<s32>(x, y, x + 20, y + 15), false, false,
                        addPlanetWindow);
  x += 32;
  zVelEditBox = guienv->addEditBox(L"", rect<s32>(x, y, x + 64, y + 15), true,
                                   addPlanetWindow);
  createPlanetButton = guienv->addButton(rect<s32>(200, 500, 300, 550),
                                         addPlanetWindow, 1, L"Create Planet");

  x = 50;
  y += 60;

  // add edit boxes for orbit input

  guienv->addStaticText(L"Orbital Elements", rect<s32>(x, y, x + 60, y + 15),
                        false, false, addPlanetWindow);
  x += 64;
  guienv->addStaticText(L"r:", rect<s32>(x, y, x + 20, y + 15), false, false,
                        addPlanetWindow);
  x += 32;
  radiusEditBox = guienv->addEditBox(L"", rect<s32>(x, y, x + 64, y + 15), true,
                                     addPlanetWindow);
  x += 88;
  guienv->addStaticText(L"e:", rect<s32>(x, y, x + 20, y + 15), false, false,
                        addPlanetWindow);
  x += 32;
  eccentriciyEditBox = guienv->addEditBox(L"", rect<s32>(x, y, x + 64, y + 15),
                                          true, addPlanetWindow);
  x += 88;
  guienv->addStaticText(L"i:", rect<s32>(x, y, x + 20, y + 15), false, false,
                        addPlanetWindow);
  x += 32;
  inclinationEditBox = guienv->addEditBox(L"", rect<s32>(x, y, x + 64, y + 15),
                                          true, addPlanetWindow);
  x = 50;
  y += 30;

  // add edit boxes for advanced orbital characteristics

  guienv->addStaticText(L"Advanced", rect<s32>(x, y, x + 60, y + 15), false,
                        true, addPlanetWindow);
  x += 64;
  guienv->addStaticText(L"ArgP", rect<s32>(x, y, x + 20, y + 45), false, true,
                        addPlanetWindow);
  x += 32;
  argpEditBox = guienv->addEditBox(L"0", rect<s32>(x, y, x + 64, y + 15), true,
                                   addPlanetWindow);
  x += 88;
  guienv->addStaticText(L"Right Asc", rect<s32>(x, y, x + 20, y + 45), false,
                        true, addPlanetWindow);
  x += 32;
  rightAscensionEditBox = guienv->addEditBox(
      L"0", rect<s32>(x, y, x + 64, y + 15), true, addPlanetWindow);
  x += 88;
  guienv->addStaticText(L"True anomaly", rect<s32>(x, y, x + 20, y + 45), false,
                        true, addPlanetWindow);
  x += 32;
  trueAnomalyEditBox = guienv->addEditBox(L"0", rect<s32>(x, y, x + 64, y + 15),
                                          true, addPlanetWindow);

  createPlanetButton = guienv->addButton(rect<s32>(200, 500, 300, 550),
                                         addPlanetWindow, 1, L"Create Planet");

  warningText = guienv->addStaticText(L"", rect<s32>(115, 560, 385, 580), false,
                                      false, addPlanetWindow);

  receiver->setPlanetWindowSate(true);
}

bool GUI::createPlanetFromInput() {

  if (inputTypeSelect->getSelected() == 0) {
    // create orbit based on state vectors

    try {
      double xPos = std::stod(std::wstring(xPosEditBox->getText()));
      double yPos = std::stod(std::wstring(yPosEditBox->getText()));
      double zPos = std::stod(std::wstring(zPosEditBox->getText()));
      double xVel = std::stod(std::wstring(xVelEditBox->getText()));
      double yVel = std::stod(std::wstring(yVelEditBox->getText()));
      double zVel = std::stod(std::wstring(zVelEditBox->getText()));

      addPlanet(Vector(xPos, yPos, zPos), Vector(xVel, yVel, zVel),
                planetSelect->getSelected());
      return true;
    } catch (const std::exception &e) {
      warningText->setText(L"Warning: ensure that all text boxes contain only "
                           L"numerical digits or symbols");

      return false;
    }
  }

  else if (inputTypeSelect->getSelected() == 1) {
    // create orbit based on orbital characteristics

    try {

      double radius = std::stod(std::wstring(radiusEditBox->getText()));
      double eccentricity =
          std::stod(std::wstring(eccentriciyEditBox->getText()));
      double inclination =
          std::stod(std::wstring(inclinationEditBox->getText()));
      double argp = std::stod(std::wstring(argpEditBox->getText()));
      double rightAscension =
          std::stod(std::wstring(rightAscensionEditBox->getText()));
      double trueAnomaly =
          std::stod(std::wstring(trueAnomalyEditBox->getText()));

      // convert angles into radians and make them between 0 and 2pi

      inclination -= 90;
      inclination = inclination * CONST_PI / 180;
      inclination = fmod(inclination, 2 * CONST_PI);

      argp = argp * CONST_PI / 180;
      argp = fmod(argp, 2 * CONST_PI);

      trueAnomaly = trueAnomaly * CONST_PI / 180;
      trueAnomaly = fmod(trueAnomaly, 2 * CONST_PI);

      // check eccentricity is between 0 (inclusive) and 1 (exclusive)

      if (eccentricity < 0) {

        warningText->setText(
            L"Eccentricity must be greater than or equal to 0");

        return false;
      }

      if (eccentricity >= 1) {

        warningText->setText(L"Eccentricity must be less than 1");

        return false;
      }

      // check radius is greater than or equal to 0

      if (radius <= 0) {

        warningText->setText(L"Radius Input must be positive");

        return false;
      }

      std::weak_ptr<Planet> selectedPlanet =
          pm.getPlanetFromSceneNode(camera->getPlanet()).lock();

      if (selectedPlanet.lock()) {

        double mu = selectedPlanet.lock()->getMass() * CONST_G;

        double angularMomentum = sqrt(mu * radius * (1 - pow(eccentricity, 2)));

        Orbit o = Orbit(angularMomentum, inclination, eccentricity,
                        rightAscension, argp, trueAnomaly);

        pos_and_vel posVel = o.orbitalElementsToStateVectors(selectedPlanet);

        addPlanet(posVel.position, posVel.velocity,
                  planetSelect->getSelected());
      } else {
        warningText->setText(L"Please ensure a planet is selected before "
                             L"trying to add planet");
        return false;
      }
      return true;
    } catch (const std::exception &e) {
      warningText->setText(L"Warning: ensure that all text boxes contain only "
                           L"numerical digits or symbols");

      return false;
    }
  }
  std::cerr << "error with drop down selection menu\n";
  return false;
}

void GUI::openTitleScreen() {

  startSimulationButton = guienv->addButton(rect<s32>(793, 500, 983, 600),
                                            nullptr, -1, L"Start Simulation");

  advancedStartButton = guienv->addButton(rect<s32>(793, 630, 983, 730),
                                          nullptr, -1, L"Advanced");

  titleText = guienv->addImage(rect<s32>(593, 100, 1183, 400));
  titleText->setImage(driver->getTexture("assets/titleScreen.png"));
  titleText->setScaleImage(true);
}

void GUI::handleTitleScreenButtons() {

  if (advancedStartButton->isPressed()) {

    if (!advancedMenuPressed) { // for not allowing multiple presses to
                                // be detected from single press

      if (advancedStartsOpen) { // menu already open - close it

        emptySimulationButton->remove();
        binaryStartButton->remove();

        advancedStartsOpen = false;

      } else { // menu is closed - open it

        emptySimulationButton = guienv->addButton(rect<s32>(793, 760, 983, 860),
                                                  nullptr, -1, L"Start Empty");

        binaryStartButton = guienv->addButton(rect<s32>(793, 890, 983, 990),
                                              nullptr, -1, L"Start Binary");

        advancedStartsOpen = true;
      }

      advancedMenuPressed = true;
    }

  } else { // button is not pressed, so now a new press can be detected
    advancedMenuPressed = false;
  }

  if (startSimulationButton->isPressed()) {

    createTopBar();
    addStartingPlanets();

    titleScreenOpen = false;

    titleText->remove();
    startSimulationButton->remove();
    advancedStartButton->remove();

    if (advancedStartsOpen) {

      emptySimulationButton->remove();
      binaryStartButton->remove();
    }

    startType = _Normal;
  }

  else if (advancedStartsOpen) {
    if (emptySimulationButton->isPressed()) {

      createTopBar();

      titleScreenOpen = false;

      titleText->remove();
      startSimulationButton->remove();
      advancedStartButton->remove();

      emptySimulationButton->remove();
      binaryStartButton->remove();

      startType = _Empty;

    } else if (binaryStartButton->isPressed()) {

      createTopBar();
      createBinarySystem();

      titleScreenOpen = false;

      titleText->remove();
      startSimulationButton->remove();
      advancedStartButton->remove();

      emptySimulationButton->remove();
      binaryStartButton->remove();

      startType = _Binary;
    }
  }
}

void GUI::createBinarySystem() {}

void GUI::createPlanetMenu(std::weak_ptr<Planet> planet) {

  if (planet.lock()) {
    std::shared_ptr<Planet> p = planet.lock();

    if (receiver->getPlanetMenuState()) {
      planetMenu->remove();
    }

    planetMenu = guienv->addWindow(rect<s32>(400, 200, 700, 650), false,
                                   L"Planet Menu", nullptr, _PlanetMenu);
    // width 350, height 500

    int x = 125;
    int y = 100;

    guienv->addStaticText(L"Mass:", rect<s32>(x - 100, y, x - 25, y + 25),
                          false, false, planetMenu);

    std::wstring massString = std::to_wstring((double)p->getMass());
    const wchar_t *massArray = massString.c_str();

    massText =
        guienv->addStaticText(massArray, rect<s32>(x - 50, y, x - 25, y + 25),
                              false, false, planetMenu);

    massSlider = guienv->addScrollBar(true, rect<s32>(x, y, x + 150, y + 25),
                                      planetMenu);
    massSlider->setMin(0);
    massSlider->setMax(100);
    massSlider->setSmallStep(1);

    massSlider->setPos(round(10 * log10((double)p->getMass())));
    // mass slider uses logarithmic scale

    y += 40;

    guienv->addStaticText(L"Radius:", rect<s32>(x - 100, y, x - 25, y + 25),
                          false, false, planetMenu);

    std::wstring radiusString = std::to_wstring(p->getRadius());
    const wchar_t *radiusArray = radiusString.c_str();

    radiusText =
        guienv->addStaticText(radiusArray, rect<s32>(x - 50, y, x - 25, y + 25),
                              false, false, planetMenu);

    radiusSlider = guienv->addScrollBar(true, rect<s32>(x, y, x + 150, y + 25),
                                        planetMenu);
    radiusSlider->setMin(0);
    radiusSlider->setMax(100);
    radiusSlider->setSmallStep(1);

    radiusSlider->setPos(sqrt(p->getRadius()) / 2.3);
    // radius slider uses polynomial scale

    y += 40;

    guienv->addStaticText(L"Eccentricity:",
                          rect<s32>(x - 100, y, x - 25, y + 25), false, false,
                          planetMenu);

    std::wstring eccentricityString = std::to_wstring(p->getEccentricity());
    const wchar_t *eccentricityArray = eccentricityString.c_str();

    eccentricityText = guienv->addStaticText(
        eccentricityArray, rect<s32>(x - 50, y, x - 25, y + 25), false, false,
        planetMenu);

    eccentricitySlider = guienv->addScrollBar(
        true, rect<s32>(x, y, x + 150, y + 25), planetMenu);
    eccentricitySlider->setMin(0);
    eccentricitySlider->setMax(100);
    eccentricitySlider->setSmallStep(1);

    eccentricitySlider->setPos(p->getEccentricity() * 100);

    y += 40;

    guienv->addStaticText(L"Inclination", rect<s32>(x - 100, y, x - 25, y + 25),
                          false, false, planetMenu);

    double inclination = fmod((p->getInclination() * 180 / CONST_PI) - 90, 180);

    std::wstring inclinationString = std::to_wstring(inclination);
    const wchar_t *inclinationArray = inclinationString.c_str();

    inclinationText = guienv->addStaticText(
        inclinationArray, rect<s32>(x - 50, y, x - 25, y + 25), false, false,
        planetMenu);

    inclinationSlider = guienv->addScrollBar(
        true, rect<s32>(x, y, x + 150, y + 25), planetMenu);
    inclinationSlider->setMin(0);
    inclinationSlider->setMax(180);
    inclinationSlider->setSmallStep(1);

    inclinationSlider->setPos(inclination);

    receiver->setPlanetMenuState(true);
    planetInMenu = planet;

    deletePlanetButton = guienv->addButton(rect<s32>(100, 35, 200, 85),
                                           planetMenu, -1, L"Delete Planet");

    x = 25;
    y += 60;

    guienv->addStaticText(L"Kinetic Energy:", rect<s32>(x, y, x + 100, y + 40),
                          false, true, planetMenu);

    std::wstring kineticEnergyString = std::to_wstring(p->getKineticEnergy());
    const wchar_t *kineticEnergyArray = kineticEnergyString.c_str();

    kineticEnergyText = guienv->addStaticText(
        kineticEnergyArray, rect<s32>(x + 100, y, x + 200, y + 40), false,
        false, planetMenu);
    y += 40;

    guienv->addStaticText(L"Gravitational Potential Energy:",
                          rect<s32>(x, y, x + 100, y + 40), false, true,
                          planetMenu);

    std::wstring gravitationalEnergyString =
        std::to_wstring(p->getGravitationalEnergy());
    const wchar_t *gravitationalEnergyArray = gravitationalEnergyString.c_str();

    gravitationalEnergyText = guienv->addStaticText(
        gravitationalEnergyArray, rect<s32>(x + 100, y, x + 200, y + 40), false,
        false, planetMenu);
    y += 40;

    guienv->addStaticText(L"Total Energy:", rect<s32>(x, y, x + 100, y + 40),
                          false, true, planetMenu);

    std::wstring totalEnergyString =
        std::to_wstring(p->getGravitationalEnergy() + p->getKineticEnergy());
    const wchar_t *totalEnergyArray = totalEnergyString.c_str();

    totalEnergyText = guienv->addStaticText(
        totalEnergyArray, rect<s32>(x + 100, y, x + 200, y + 40), false, false,
        planetMenu);

  } else {
    std::cerr << "error with weak pointer not locking\n";
  }
}

void GUI::updatePlanetInMenu() {
  if (planetInMenu.lock()) {
    // update the planet attributes based on value of the sliders
    std::shared_ptr<Planet> p = planetInMenu.lock();

    // update planet values based on slider positions

    double m = pow(10, massSlider->getPos() / 10.0);

    p->setMass(m);

    double r = 5.29 * pow(radiusSlider->getPos(), 2);

    p->setRadius(r);

    double e = (double)eccentricitySlider->getPos() / 100;

    if (e == 0) {
      // avoid eccentricity of exactly 0, since it causes zero divition
      e = 0.01;
    }

    if (e == 1) {
      e = 0.99; // avoid eccentricity of 1, since it is escape trajectory
    }

    double inclination = inclinationSlider->getPos() + 90;

    inclination = fmod(inclination, 180);

    if (inclination == 0) {
      inclination = 0.01; // avoid zero and 180 inclination, as they causes
                          // screen flickering
    } else if (inclination == 180) {
      inclination = 179.9;
    }

    p->setInclination(inclination * CONST_PI / 180);

    p->setEccentricity(e);

    // update text based on planet values

    std::wstring massString = std::to_wstring((double)p->getMass());
    const wchar_t *massArray = massString.c_str();

    massText->setText(massArray);

    std::wstring radiusString = std::to_wstring(p->getRadius());
    const wchar_t *radiusArray = radiusString.c_str();

    radiusText->setText(radiusArray);

    std::wstring eccentricityString = std::to_wstring(p->getEccentricity());
    const wchar_t *eccentricityArray = eccentricityString.c_str();

    eccentricityText->setText(eccentricityArray);

    std::wstring inclinationString =
        std::to_wstring(inclinationSlider->getPos());
    const wchar_t *inclinationArray = inclinationString.c_str();

    inclinationText->setText(inclinationArray);

    std::wstring kineticEnergyString = std::to_wstring(p->getKineticEnergy());
    const wchar_t *kineticEnergyArray = kineticEnergyString.c_str();

    kineticEnergyText->setText(kineticEnergyArray);

    std::wstring gravitationalEnergyString =
        std::to_wstring(p->getGravitationalEnergy());
    const wchar_t *gravitationalEnergyArray = gravitationalEnergyString.c_str();

    gravitationalEnergyText->setText(gravitationalEnergyArray);

    std::wstring totalEnergyString =
        std::to_wstring(p->getGravitationalEnergy() + p->getKineticEnergy());
    const wchar_t *totalEnergyArray = totalEnergyString.c_str();

    totalEnergyText->setText(totalEnergyArray);

    if (deletePlanetButton->isPressed()) {
      pm.removePlanet(planetInMenu);

      planetMenu->remove();
      receiver->setPlanetMenuState(false);
    }

  } else {
    // delete the menu

    planetMenu->remove();
    receiver->setPlanetMenuState(false);
  }
}
