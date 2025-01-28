#include "main/planets/Ringed.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>
Ringed::Ringed(const Vector &_position, const Vector &_velocity,
               irr::scene::ISceneManager *smgr,
               irr::video::IVideoDriver *driver)
    : Planet(_position, _velocity, smgr, driver) {

  size = 100;
  mass = 500;
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/ringed.jpg";

  // based off of saturn

  if (obj) {

    obj->setName("Ringed");
    obj->setScale(irr::core::vector3df(size, size, size));
    if (driver) {

      irr::video::ITexture *texture = driver->getTexture(pathToTexture);

      obj->setMaterialTexture(0, texture);

      obj->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
  }
}

void Ringed::drawPlanet(irr::video::IVideoDriver *driver) {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));

  orbit.drawOrbit(orbitedPlanet, driver);
}
