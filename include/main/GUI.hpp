#pragma once

#include "main/PlanetManager.hpp"

#include <irrlicht.h>
#include <map>

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

  PlanetManager pm;

  std::map<irr::scene::ISceneNode *, std::weak_ptr<irr::scene::ISceneNode>>
      scenePointerMap;

  irr::IrrlichtDevice *device;

  irr::video::IVideoDriver *driver;
  irr::scene::ISceneManager *smgr;
  irr::gui::IGUIEnvironment *guienv;
  irr::scene::ISceneCollisionManager *colmgr;
};
