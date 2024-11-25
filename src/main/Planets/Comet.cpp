#include "main/planets/Comet.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>

Comet::Comet(const Vector &_position, const Vector &_velocity,
             irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity) {

  size = 4 * pow(10, 3);
  mass = 3 * pow(10, 14);
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // radius and mass based off of halley's comet

  if (smgr) {

    obj = smgr->addSphereSceneNode(size, 20);

    if (obj) {
      obj->setPosition(
          irr::core::vector3df(position.x, position.y, position.z));
    }
  } else {
    obj = nullptr;
  }
}

void Comet::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}

// getters and setters
__float128 Comet::getSize() { return size; }
