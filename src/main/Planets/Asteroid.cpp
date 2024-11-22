#include "main/planets/Asteroid.hpp"
#include "main/Planet.hpp"
#include "vector3d.h"

#include <cmath>
#include <irrlicht.h>

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity,
                   irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity) {

  size = 2 * pow(10, 2);
  mass = 2 * pow(10, 9);
  rotation_rate = 10;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // mass and radius of typical medium asteroid

  if (smgr) {

    obj = smgr->addSphereSceneNode(size, 20);

    if (obj) {
      obj->setPosition(
          irr::core::vector3df(position.x, position.y, position.z));
    }
  }
}

void Asteroid::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}

// getters and setters
__float128 Asteroid::getSize() { return size; }
