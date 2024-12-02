#include "main/planets/Gas.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>
Gas::Gas(const Vector &_position, const Vector &_velocity,
         irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity, smgr) {

  size = 7 * pow(10, 7);
  mass = 2 * pow(10, 27);
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off of jupiter
  if (smgr) { // check if smgr is not null

    obj = smgr->addSphereSceneNode(size, 20);

    if (obj) { // check obj initialised correctly
      obj->setPosition(
          irr::core::vector3df(position.x, position.y, position.z));
    }
  }
}

void Gas::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
