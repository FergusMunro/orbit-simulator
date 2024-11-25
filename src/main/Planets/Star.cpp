#include "main/planets/Star.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>
Star::Star(const Vector &_position, const Vector &_velocity,
           irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity) {

  size = 7 * pow(10, 8);
  mass = 2 * pow(10, 30);
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off sun

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

void Star::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}

// getters and setters
__float128 Star::getSize() { return size; }
