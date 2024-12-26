#include "main/planets/Telluric.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>
Telluric::Telluric(const Vector &_position, const Vector &_velocity,
                   irr::scene::ISceneManager *smgr,
                   irr::video::IVideoDriver *driver)
    : Planet(_position, _velocity, smgr, driver) {

  size = 30;
  mass = 100;
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off of earth

  if (obj) {

    obj->setName("Telluric");
    obj->setScale(irr::core::vector3df(size, size, size));
  }
}

void Telluric::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
