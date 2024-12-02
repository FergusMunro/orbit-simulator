#include "main/GUI.hpp"
#include "main/Macros.hpp"

#include <cmath>
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

  // forever loop that updates positions of planets and then draws planets

  ICameraSceneNode *camera = gui.smgr->addCameraSceneNode();

  camera->setFarValue(1e6);

  gui.pm.addPlanet(Vector(0, 0, 4e2), Vector(0, 0, 0), gui.smgr, _Asteroid);

  // gui.pm.addPlanet(Vector(0, 0, 1 * pow(10, 5)), Vector(0, 0, 0), gui.smgr,
  //                 _Comet);

  // gui.pm.addPlanet(Vector(0, 0, pow(10, 1)), Vector(0, 0, 0), gui.smgr,
  //                 _Satellite);

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
