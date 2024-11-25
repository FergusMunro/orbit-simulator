#include "main/planets/Telluric.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>
Telluric::Telluric(const Vector &_position, const Vector &_velocity,
                   irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity) {

  size = 6 * pow(10, 6);
  mass = 6 * pow(10, 24);
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off of earth
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

void Telluric::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}

// getters and setters
__float128 Telluric::getSize() { return size; }
