#include "main/GUI.hpp"
#include "main/CameraManager.hpp"
#include "main/EventReciever.hpp"
#include "main/Macros.hpp"

#include "vector2d.h"
#include <cmath>
#include <iostream>
#include <irrlicht.h>
#include <memory>
#include <string>
#include <vector>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int findRawPointer(std::vector<std::weak_ptr<irr::scene::ISceneNode>> items,
                   void *ptr) {
  for (int i = 0; i < items.size(); i++) {
    if (items[i].lock().get() == ptr) {
      return i;
    }
  }

  std::cerr << "somehow pointer shenanigans\n";
  return -1;
}

GUI::GUI() {
  device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1000, 1000), 16,
                        true, false, false, 0);

  if (!device) {
    std::cerr << "no device\n";
  }

  device->setWindowCaption(L"Orbit Simulator");

  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  guienv = device->getGUIEnvironment();

  if (!driver || !smgr || !guienv) {
    std::cerr << "problem with initialisation\n";
  }

  pm = PlanetManager();
}

void GUI::run() {
  // runs constructor

  GUI gui = GUI();

  std::vector<std::weak_ptr<irr::scene::ISceneNode>> scenePointers;

  ISceneCollisionManager *colmgr = gui.smgr->getSceneCollisionManager();

  // forever loop that updates positions of planets and then draws planets

  CameraManager camera = CameraManager(gui.smgr);

  scenePointers.push_back(
      gui.pm.addPlanet(Vector(0, 0, 10000), Vector(0, 0, 0), gui.smgr, _Star));

  scenePointers.push_back(
      gui.pm.addPlanet(Vector(0, 0, 500), Vector(0, 0, 0), gui.smgr, _Gas));

  scenePointers.push_back(
      gui.pm.addPlanet(Vector(0, 0, -500), Vector(0, 0, 0), gui.smgr, _Gas));

  scenePointers.push_back(
      gui.pm.addPlanet(Vector(0, 500, 500), Vector(0, 0, 0), gui.smgr, _Gas));

  scenePointers.push_back(
      gui.pm.addPlanet(Vector(0, -500, -500), Vector(0, 0, 0), gui.smgr, _Gas));

  scenePointers.push_back(
      gui.pm.addPlanet(Vector(0, -1000, 500), Vector(0, 0, 0), gui.smgr, _Gas));

  scenePointers.push_back(
      gui.pm.addPlanet(Vector(1000, 0, -500), Vector(0, 0, 0), gui.smgr, _Gas));

  std::unique_ptr<EventReceiver> receiver = std::make_unique<EventReceiver>();
  gui.device->setEventReceiver(receiver.get());

  vector2di mousepos;
  ISceneNode *selected = nullptr;

  std::string empty = "";

  while (gui.device->run()) {
    gui.driver->beginScene(true, true, SColor(255, 100, 101, 140));

    gui.pm.updatePositions();

    gui.pm.drawPlanets();

    if (receiver->GetMouseState().LeftButtonDown) {

      mousepos = receiver->GetMouseState().Position;
      selected = colmgr->getSceneNodeFromScreenCoordinatesBB(
          vector2d(mousepos.X, mousepos.Y));

      if (selected) { // check that it's not nullptr

        if (empty.compare(selected->getName())) { // check is name is not empty
                                                  // - if name is empty then we
                                                  // are looking at nothing

          camera.setSelectedPlanet(
              scenePointers[findRawPointer(scenePointers, selected)]);
        }
      }
    }

    gui.smgr->drawAll();
    gui.guienv->drawAll();

    camera.updatePosition();

    gui.driver->endScene();
  }

  gui.pm.removeAll();

  gui.device->drop();
}
