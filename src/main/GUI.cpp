#include "main/GUI.hpp"
#include "main/planets/Telluric.hpp"
#include "vector3d.h"

#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

GUI::GUI() {
  Telluric t = Telluric(Vector(0, 0, 0), Vector(0, 0, 0));

  pm.addPlanet(std::make_unique<Telluric>(t));

  // basic driver code to set up a basic simulation
}

void GUI::run() {
  // runs constructor

  GUI gui = GUI();

  // forever loop that updates positions of planets and then draws planets

  IrrlichtDevice *device =
      createDevice(video::EDT_OPENGL, dimension2d<u32>(1800, 1000), 16, true,
                   false, false, 0);

  device->setWindowCaption(L"Orbit Simulator");

  IVideoDriver *driver = device->getVideoDriver();
  ISceneManager *smgr = device->getSceneManager();
  IGUIEnvironment *guienv = device->getGUIEnvironment();

  while (device->run()) {

    driver->beginScene(true, true, SColor(255, 100, 101, 140));
    smgr->drawAll();
    guienv->drawAll();

    driver->endScene();
  }

  device->drop();
}
