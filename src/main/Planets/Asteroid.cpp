#include "main/planets/Asteroid.hpp"
#include "main/Planet.hpp"
#include "vector3d.h"

#include <cmath>
#include <irrlicht.h>

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity,
                   irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity, smgr) {

  size = 1;
  mass = 0;
  rotation_rate = 10;
  pathToTexture = "assets/planetTextures/asteroid.jpg";
  // mass and radius of typical medium asteroid
  if (smgr) { // check if smgr is not null

    obj = smgr->addSphereSceneNode(size, 20);

    if (obj) { // check obj initialised correctly
      obj->setPosition(
          irr::core::vector3df(position.x, position.y, position.z));
    }
  }
}

void Asteroid::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
