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

    obj = smgr->addSphereSceneNode(
        size, 16, nullptr, 0,
        irr::core::vector3df(position.x, position.y, position.z));

  } else {

    obj = nullptr;
  }
}

void Satellite::drawPlanet() {
  // TODO
}

// getters and setters
__float128 Satellite::getSize() { return size; }
