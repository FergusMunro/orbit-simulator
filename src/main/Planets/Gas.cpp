#include "main/planets/Gas.hpp"
#include "main/Planet.hpp"
#include <cmath>
#include <irrlicht.h>
Gas::Gas(const Vector &_position, const Vector &_velocity,
         irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver)
    : Planet(_position, _velocity, smgr, driver) {

  size = 120;
  mass = 1000;
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/gas.jpg";

  // based off of jupiter

  if (obj) {

    obj->setName("Gas");
    obj->setScale(irr::core::vector3df(size, size, size));
    if (driver) {

      irr::video::ITexture *texture = driver->getTexture(pathToTexture);

      obj->setMaterialTexture(0, texture);

      obj->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
  }
}

void Gas::drawPlanet(irr::video::IVideoDriver *driver) {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));

  orbit.drawOrbit(orbitedPlanet, driver);
}
