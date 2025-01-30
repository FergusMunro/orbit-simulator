#include "main/GUI.hpp"
#include "IGUIButton.h"
#include "IGUIComboBox.h"
#include "main/CameraManager.hpp"
#include "main/EventReciever.hpp"
#include "main/Macros.hpp"

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

  gui.createTopBar();
  gui.addStartingPlanets();

  // adds some misc utility variables

  ITimer *timer = gui.device->getTimer();
  double lastTime = timer->getTime();

  // forever loop that updates positions of planets and then draws planets

  while (gui.device->run()) {

    gui.driver->beginScene(true, true, SColor(255, 10, 10, 10));

    gui.pm.updatePositions((timer->getTime() - lastTime) / 1000);
    gui.pm.drawPlanets(gui.driver);

    gui.handleMouseInput();
    gui.handleButtonPresses();
    gui.camera->updatePosition();

    gui.smgr->drawAll();
    gui.guienv->drawAll();

    gui.driver->endScene();

    lastTime = timer->getTime();
    gui.receiver->update();

    if (gui.receiver->getPlanetWindowState()) {
      gui.planetSelect->getSelected();
    }
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
    addStartingPlanets();
  }

  if (addPlanetButton->isPressed()) {
    createAddPlanetPopUp();
  } else {
    openPopUpFlag = true;
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
}

void GUI::createAddPlanetPopUp() {

  if (openPopUpFlag) {

    addPlanetWindow =
        guienv->addWindow(rect<s32>(600, 200, 1100, 800), true, L"Add Planet");
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
    createPlanetButton = guienv->addButton(
        rect<s32>(200, 500, 300, 550), addPlanetWindow, 1, L"Create Planet");

    x = 50;
    y += 60;

    // add edit boxes for orbit input

    guienv->addStaticText(L"Orbital Elements", rect<s32>(x, y, x + 60, y + 15),
                          false, false, addPlanetWindow);
    x += 64;
    guienv->addStaticText(L"r:", rect<s32>(x, y, x + 20, y + 15), false, false,
                          addPlanetWindow);
    x += 32;
    radiusEditBox = guienv->addEditBox(L"", rect<s32>(x, y, x + 64, y + 15),
                                       true, addPlanetWindow);
    x += 88;
    guienv->addStaticText(L"e:", rect<s32>(x, y, x + 20, y + 15), false, false,
                          addPlanetWindow);
    x += 32;
    eccentriciyEditBox = guienv->addEditBox(
        L"", rect<s32>(x, y, x + 64, y + 15), true, addPlanetWindow);
    x += 88;
    guienv->addStaticText(L"i:", rect<s32>(x, y, x + 20, y + 15), false, false,
                          addPlanetWindow);
    x += 32;
    inclinationEditBox = guienv->addEditBox(
        L"", rect<s32>(x, y, x + 64, y + 15), true, addPlanetWindow);
    x = 50;
    y += 30;

    // add edit boxes for advanced orbital characteristics

    guienv->addStaticText(L"Advanced", rect<s32>(x, y, x + 60, y + 15), false,
                          true, addPlanetWindow);
    x += 64;
    guienv->addStaticText(L"ArgP", rect<s32>(x, y, x + 20, y + 45), false, true,
                          addPlanetWindow);
    x += 32;
    argpEditBox = guienv->addEditBox(L"0", rect<s32>(x, y, x + 64, y + 15),
                                     true, addPlanetWindow);
    x += 88;
    guienv->addStaticText(L"Right Asc", rect<s32>(x, y, x + 20, y + 45), false,
                          true, addPlanetWindow);
    x += 32;
    rightAscensionEditBox = guienv->addEditBox(
        L"0", rect<s32>(x, y, x + 64, y + 15), true, addPlanetWindow);
    x += 88;
    guienv->addStaticText(L"True anomaly", rect<s32>(x, y, x + 20, y + 45),
                          false, true, addPlanetWindow);
    x += 32;
    trueAnomalyEditBox = guienv->addEditBox(
        L"0", rect<s32>(x, y, x + 64, y + 15), true, addPlanetWindow);
    createPlanetButton = guienv->addButton(
        rect<s32>(200, 500, 300, 550), addPlanetWindow, 1, L"Create Planet");

    openPopUpFlag = false;
    receiver->setPlanetWindowSate(true);
  }
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
      guienv->addStaticText(L"Warning: ensure that all text boxes contain only "
                            L"numerical digits or symbols",
                            rect<s32>(115, 560, 385, 580), false, false,
                            addPlanetWindow);
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

      inclination = inclination * CONST_PI / 180;
      inclination = fmod(inclination, 2 * CONST_PI);

      argp = argp * CONST_PI / 180;
      argp = fmod(argp, 2 * CONST_PI);

      trueAnomaly = trueAnomaly * CONST_PI / 180;
      trueAnomaly = fmod(trueAnomaly, 2 * CONST_PI);

      return false;
    } catch (const std::exception &e) {
      guienv->addStaticText(L"Warning: ensure that all text boxes contain only "
                            L"numerical digits or symbols",
                            rect<s32>(115, 560, 385, 580), false, false,
                            addPlanetWindow);

      return false;
    }
  }
  std::cerr << "error with drop down selection menu\n";
  return false;
}
