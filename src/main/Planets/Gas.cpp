#include "main/planets/Gas.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>
Gas::Gas(const Vector &_position, const Vector &_velocity,
         irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity) {

  size = 7 * pow(10, 7);
  mass = 2 * pow(10, 27);
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off of jupiter

  if (smgr) {

    obj = smgr->addSphereSceneNode(
        size, 16, nullptr, 0,
        irr::core::vector3df(position.x, position.y, position.z));

  } else {

    obj = nullptr;
  }
}

void Gas::drawPlanet() {
  // TODO
}

// getters and setters
__float128 Gas::getSize() { return size; }
