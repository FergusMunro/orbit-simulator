#include "main/planets/Satellite.hpp"
#include "main/Planet.hpp"
#include <irrlicht.h>
Satellite::Satellite(const Vector &_position, const Vector &_velocity,
                     irr::scene::ISceneManager *smgr)
    : Planet(_position, _velocity) {

  size = 1;
  mass = 10;
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based of very small satellite

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

void Satellite::drawPlanet() {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}

// getters and setters
__float128 Satellite::getSize() { return size; }
