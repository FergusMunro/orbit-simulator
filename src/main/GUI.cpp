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
    gui.pm.drawPlanets();

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

    pm.removeAll();
    camera->reset();
    scenePointerMap.clear();

    // re-add planets from start of simulation
    addStartingPlanets();
  }

  if (addPlanetButton->isPressed()) {

    if (openPopUpFlag) {

      addPlanetWindow = guienv->addWindow(rect<s32>(600, 200, 1100, 800), true,
                                          L"Add Planet");
      // width = 500, height = 600

      // rect<s32>(25, 25, 475, 265)

      planetSelect =
          guienv->addComboBox(rect<s32>(180, 280, 320, 310), addPlanetWindow);

      int x = 70;
      int y = 55;

      IGUIImage *starImage =
          guienv->addImage(rect<s32>(x, y, x + 90, y + 90), addPlanetWindow);
      starImage->setImage(driver->getTexture("assets/planetIcons/star.png"));
      starImage->setScaleImage(true);

      x += 135;

      IGUIImage *ringedImage =
          guienv->addImage(rect<s32>(x, y, x + 90, y + 90), addPlanetWindow);
      ringedImage->setImage(
          driver->getTexture("assets/planetIcons/ringed.png"));
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

      planetSelect->addItem(L"Asteroid");
      planetSelect->addItem(L"Comet");
      planetSelect->addItem(L"Gas");
      planetSelect->addItem(L"Ringed");
      planetSelect->addItem(L"Star");
      planetSelect->addItem(L"Telluric");

      createPlanetButton = guienv->addButton(
          rect<s32>(200, 525, 300, 575), addPlanetWindow, 1, L"Create Planet");

      openPopUpFlag = false;
      receiver->setPlanetWindowSate(true);
    }
  } else {
    openPopUpFlag = true;
  }
}

void GUI::addStartingPlanets() {

  addPlanet(Vector(0, 0, 0), Vector(0, 0, 0), _Star);

  addPlanet(Vector(0, 0, 3000), Vector(1825, 0, 0), _Telluric);
  addPlanet(Vector(0, 0, 6000), Vector(1290, 0, 0), _Telluric);
  addPlanet(Vector(0, 0, 6050), Vector(1431, 0, 0), _Comet);
  addPlanet(Vector(0, 0, 10000), Vector(1000, 0, 0), _Gas);
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
