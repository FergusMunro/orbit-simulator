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
  device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1920, 1080), 16,
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

  gui.addPlanet(Vector(0, 0, 0), Vector(0, 0, 0), _Star);

  gui.addPlanet(Vector(0, 0, 3000), Vector(1825, 0, 0), _Telluric);
  gui.addPlanet(Vector(0, 0, 6000), Vector(1290, 0, 0), _Telluric);
  gui.addPlanet(Vector(0, 0, 6050), Vector(1431, 0, 0), _Comet);
  gui.addPlanet(Vector(0, 0, 10000), Vector(1000, 0, 0), _Gas);
  gui.addPlanet(Vector(0, 0, 15000), Vector(816, 0, 0), _Ringed);
  gui.addPlanet(Vector(0, 0, 30000), Vector(577, 0, 0), _Telluric);

  // forever loop that updates positions of planets and then draws planets

  CameraManager camera = CameraManager(gui.smgr);

  std::unique_ptr<EventReceiver> receiver = std::make_unique<EventReceiver>();
  gui.device->setEventReceiver(receiver.get());

  vector2di mousepos;
  ISceneNode *selected = nullptr;

  std::string empty = "";

  ITimer *timer = gui.device->getTimer();
  double lastTime = timer->getTime();

  while (gui.device->run()) {
    gui.driver->beginScene(true, true, SColor(255, 100, 101, 140));

    gui.pm.updatePositions((timer->getTime() - lastTime) / 1000);

    gui.pm.drawPlanets();

    // handle moving of camera

    if (receiver->GetMouseState().leftButtonDown) {
      camera.updateAngles(receiver->GetMouseState().Position);
    } else {
      camera.resetDelta();
    }

    camera.updateRadius(receiver->GetMouseState().wheel);

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

    camera.updatePosition();

    gui.smgr->drawAll();
    gui.guienv->drawAll();

    gui.driver->endScene();

    lastTime = timer->getTime();
    receiver->update();
  }

  gui.pm.removeAll();

  gui.device->drop();
}
