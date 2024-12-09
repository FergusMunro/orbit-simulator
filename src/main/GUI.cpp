#include "main/GUI.hpp"
#include "main/EventReciever.hpp"
#include "main/Macros.hpp"

#include "vector2d.h"
#include <cmath>
#include <iostream>
#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

GUI::GUI() {
  device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1000, 1000), 16,
                        true, false, false, 0);

  device->setWindowCaption(L"Orbit Simulator");

  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  guienv = device->getGUIEnvironment();

  pm = PlanetManager();
}

void GUI::run() {
  // runs constructor

  GUI gui = GUI();

  ISceneCollisionManager *colmgr = gui.smgr->getSceneCollisionManager();

  // forever loop that updates positions of planets and then draws planets

  ICameraSceneNode *camera = gui.smgr->addCameraSceneNodeMaya();

  camera->setPosition(vector3df(0, 0, 0));

  camera->setFarValue(1e6);

  gui.pm.addPlanet(Vector(0, 9000000, 0), Vector(0, 0, 0), gui.smgr, _Star);

  gui.pm.addPlanet(Vector(0, 0, 1000), Vector(0, 0, 0), gui.smgr, _Gas);

  EventReceiver *receiver = new EventReceiver;
  gui.device->setEventReceiver(receiver);

  vector2di mousepos;

  while (gui.device->run()) {
    gui.pm.updatePositions();

    gui.driver->beginScene(true, true, SColor(255, 100, 101, 140));

    gui.pm.drawPlanets();

    mousepos = receiver->GetMouseState().Position;

    ISceneNode *selected = colmgr->getSceneNodeFromScreenCoordinatesBB(
        vector2d(mousepos.X, mousepos.Y));
    std::cout << selected->getName() << "\n";

    gui.smgr->drawAll();
    gui.guienv->drawAll();

    gui.driver->endScene();
  }

  gui.pm.removeAll();

  gui.device->drop();
  delete receiver;
}
