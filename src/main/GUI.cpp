#include "main/GUI.hpp"
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

void GUI::addPlanet(const Vector &_position, const Vector &_velocity,
                    int type) {

  std::weak_ptr<ISceneNode> temp =
      pm.addPlanet(_position, _velocity, smgr, driver, type);

  scenePointerMap.insert({temp.lock().get(), temp});
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

  colmgr = smgr->getSceneCollisionManager();

  if (!driver || !smgr || !guienv) {
    std::cerr << "problem with initialisation\n";
  }

  pm = PlanetManager();
}

void GUI::run() {
  // runs constructor

  GUI gui = GUI();

  gui.addPlanet(Vector(0, 0, 10000), Vector(0, 0, 0), _Star);
  gui.addPlanet(Vector(0, 0, 500), Vector(0, 0, 0), _Gas);
  gui.addPlanet(Vector(0, 0, -500), Vector(0, 0, 0), _Gas);
  gui.addPlanet(Vector(0, 500, 500), Vector(0, 0, 0), _Gas);
  gui.addPlanet(Vector(0, -500, -500), Vector(0, 0, 0), _Gas);
  gui.addPlanet(Vector(0, -1000, 500), Vector(0, 0, 0), _Gas);
  gui.addPlanet(Vector(1000, 0, -500), Vector(0, 0, 0), _Gas);

  // forever loop that updates positions of planets and then draws planets

  CameraManager camera = CameraManager(gui.smgr);

  std::unique_ptr<EventReceiver> receiver = std::make_unique<EventReceiver>();
  gui.device->setEventReceiver(receiver.get());

  vector2di mousepos;
  ISceneNode *selected = nullptr;

  std::string empty = "";

  while (gui.device->run()) {
    gui.driver->beginScene(true, true, SColor(255, 100, 101, 140));

    gui.pm.updatePositions();

    gui.pm.drawPlanets();

    // handle moving of camera

    if (receiver->GetMouseState().leftButtonDown) {
      camera.updateAngles(receiver->GetMouseState().Position);
    } else {
      camera.resetDelta();
    }

    camera.setRadius(receiver->GetMouseState().wheel);

    // handle selection of planet
    if (receiver->GetMouseState().middleButtonDown) {

      mousepos = receiver->GetMouseState().Position;
      selected = gui.colmgr->getSceneNodeFromScreenCoordinatesBB(
          vector2d(mousepos.X, mousepos.Y));

      if (selected) { // check that it's not nullptr

        if (empty.compare(selected->getName())) { // check is name is not empty
                                                  // - if name is empty then we
                                                  // are looking at nothing
          camera.setSelectedPlanet(gui.scenePointerMap[selected]);
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
