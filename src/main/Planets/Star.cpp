#include "main/planets/Star.hpp"
#include "main/Planet.hpp"
#include "vector3d.h"
#include <cmath>
#include <irrlicht.h>

Star::Star(const Vector &_position, const Vector &_velocity,
           irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity, smgr) {

  size = 600;
  mass = 1e6;
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off sun

  if (obj) {

    obj->setName("Star");
    obj->setScale(irr::core::vector3df(size, size, size));
  }
}

void Star::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
