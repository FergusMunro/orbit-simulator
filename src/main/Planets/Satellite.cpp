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
  if (smgr) { // check if smgr is not null

    obj = smgr->addSphereSceneNode(size, 20);

    if (obj) { // check obj initialised correctly
      obj->setPosition(
          irr::core::vector3df(position.x, position.y, position.z));
    }
  }
}

void Satellite::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}
