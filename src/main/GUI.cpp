#include "main/GUI.hpp"

#include <cmath>
#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

GUI::GUI() {
  device = createDevice(video::EDT_OPENGL, dimension2d<u32>(500, 500), 16, true,
                        false, false, 0);

  device->setWindowCaption(L"Orbit Simulator");

  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  guienv = device->getGUIEnvironment();

  pm = PlanetManager();
}

void GUI::run() {
  // runs constructor

  GUI gui = GUI();

  // forever loop that updates positions of planets and then draws planets

  irr::scene::ICameraSceneNode *camera =
      gui.smgr->addCameraSceneNode(0, vector3df(0, 0, 0));

  camera->setFarValue(1e6);

  gui.pm.addPlanet(Vector(0, 0, pow(10, 3)), Vector(5, -3, 0), gui.smgr);

  gui.pm.addPlanet(Vector(0, 0, pow(10, 3)), Vector(0, 3, 1), gui.smgr);

  while (gui.device->run()) {

    gui.pm.updatePositions();

    gui.driver->beginScene(true, true, SColor(255, 100, 101, 140));

    gui.pm.drawPlanets();

    gui.smgr->drawAll();
    gui.guienv->drawAll();

    gui.driver->endScene();
  }

  gui.pm.removeAll();

  gui.device->drop();
}
