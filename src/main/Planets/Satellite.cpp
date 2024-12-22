#include "main/planets/Satellite.hpp"
#include "main/Planet.hpp"
#include <irrlicht.h>

Satellite::Satellite(const Vector &_position, const Vector &_velocity,
                     irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity, smgr) {

  size = 1;
  mass = 0;
  rotation_rate = 0;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based of very small satellite

  if (obj) {

    obj->setName("Satellite");
    obj->setScale(irr::core::vector3df(size, size, size));
  }
}

void Satellite::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
