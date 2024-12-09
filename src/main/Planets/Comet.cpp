#include "main/planets/Comet.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>

Comet::Comet(const Vector &_position, const Vector &_velocity,
             irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity, smgr) {

  size = 2;
  mass = 0;
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // radius and mass based off of halley's comet
  if (smgr) { // check if smgr is not null

    obj = smgr->addSphereSceneNode(size, 20);

    if (obj) { // check obj initialised correctly
      obj->setPosition(
          irr::core::vector3df(position.x, position.y, position.z));
    }
  }
}

void Comet::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
