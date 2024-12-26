#include "main/planets/Asteroid.hpp"
#include "main/Planet.hpp"
#include "vector3d.h"

#include <cmath>
#include <irrlicht.h>

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity,
                   irr::scene::ISceneManager *smgr,
                   irr::video::IVideoDriver *driver)
    : Planet(_position, _velocity, smgr, driver) {

  size = 1;
  mass = 0;
  rotation_rate = 10;
  pathToTexture = "assets/planetTextures/asteroid.jpg";
  // mass and radius of typical medium asteroid

  if (obj) {

    obj->setName("Asteroid");
    obj->setScale(irr::core::vector3df(size, size, size));
  }
}

void Asteroid::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
