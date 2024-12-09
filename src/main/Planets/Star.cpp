#include "main/planets/Star.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>
Star::Star(const Vector &_position, const Vector &_velocity,
           irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity, smgr) {

  size = 600;
  mass = 1e6;
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off sun
  if (smgr) { // check if smgr is not null

    obj = smgr->addSphereSceneNode(size, 20);

    if (obj) { // check obj initialised correctly
      obj->setPosition(
          irr::core::vector3df(position.x, position.y, position.z));
      obj->setName("Star");
    }
  }
}

void Star::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
