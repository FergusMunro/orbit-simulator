#include "main/planets/Gas.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>
Gas::Gas(const Vector &_position, const Vector &_velocity,
         irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity, smgr) {

  size = 120;
  mass = 1000;
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off of jupiter

  if (obj) {

    obj->setName("Gas");
    obj->setScale(irr::core::vector3df(size, size, size));
  }
}

void Gas::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
