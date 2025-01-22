#pragma once

#include "main/CameraManager.hpp"
#include "main/EventReciever.hpp"
#include "main/PlanetManager.hpp"

#include <irrlicht.h>
#include <map>
#include <memory>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GUI {
public:
  static void run();

  /* This class uses a private constructor and a static method that instead
   * creates the class, which means there can only be one GUI which makes the
   * code much simpler and less easy to missuse.
   */

private:
  GUI();
  void addPlanet(const Vector &_position, const Vector &_velocity, int type);

  void createTopBar();
  void addStartingPlanets();
  void handleMouseInput();
  void handleButtonPresses();

  PlanetManager pm;
  std::unique_ptr<CameraManager> camera;

  std::map<irr::scene::ISceneNode *, std::weak_ptr<irr::scene::ISceneNode>>
      scenePointerMap;
  // reciever, mousepos,
  std::unique_ptr<EventReceiver> receiver;
  vector2di mousepos;

  IrrlichtDevice *device;

  IVideoDriver *driver;
  ISceneManager *smgr;
  IGUIEnvironment *guienv;
  ISceneCollisionManager *colmgr;

  IGUIStaticText *topBar;
  IGUIButton *pauseButton;
  IGUIButton *normalSpeedButton;
  IGUIButton *fastSpeedButton;
  IGUIButton *veryFastButton;
  IGUIButton *extremelyFastButton;
  IGUIButton *resetButton;
};
