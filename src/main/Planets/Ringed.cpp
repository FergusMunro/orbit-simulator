#include "main/planets/Ringed.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>
Ringed::Ringed(const Vector &_position, const Vector &_velocity,
               irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity, smgr) {

  size = 100;
  mass = 500;
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off of saturn
  if (smgr) { // check if smgr is not null

    obj = smgr->addSphereSceneNode(size, 20);

    if (obj) { // check obj initialised correctly
      obj->setPosition(
          irr::core::vector3df(position.x, position.y, position.z));
    }
  }
}

void Ringed::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
