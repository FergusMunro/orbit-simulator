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

  if (obj) {

    obj->setName("Comet");
    obj->setScale(irr::core::vector3df(size, size, size));
  }
}

void Comet::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
