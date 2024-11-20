#include "main/GUI.hpp"
#include "main/planets/Telluric.hpp"

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

  IrrlichtDevice *device = createDevice(
      video::EDT_OPENGL, dimension2d<u32>(640, 480), 16, true, false, false, 0);

  device->setWindowCaption(L"Orbit Simulator");

  IVideoDriver *driver = device->getVideoDriver();
  ISceneManager *smgr = device->getSceneManager();
  IGUIEnvironment *guienv = device->getGUIEnvironment();

  guienv->addStaticText(L"first gui edition of orbit simulator",
                        rect<s32>(10, 10, 260, 22), true);

  ISceneNode *sphere = smgr->addSphereSceneNode();

  sphere->setScale(vector3df(2.0f, 2.0f, 2.0f));
  sphere->setPosition(vector3df(0, 0, 30));
  sphere->setMaterialFlag(EMF_LIGHTING, false);

  smgr->addCameraSceneNode(0, vector3df(0, 0, -40), vector3df(0, 0, 30));

  while (device->run()) {

    driver->beginScene(true, true, SColor(255, 100, 101, 140));

    sphere->setPosition(sphere->getPosition() + vector3df(2, 1, 3));

    smgr->drawAll();
    guienv->drawAll();

    driver->endScene();
  }

  device->drop();
}
