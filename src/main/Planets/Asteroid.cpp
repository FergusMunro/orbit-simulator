#include "main/planets/Asteroid.hpp"
#include "main/Planet.hpp"
#include "vector3d.h"

#include <cmath>
#include <irrlicht.h>

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity,
                   irr::scene::ISceneManager *smgr,
                   irr::video::IVideoDriver *driver)
    : Planet(_position, _velocity, smgr, driver) {

  size = 1;
  mass = 0;
  rotation_rate = 10;
  pathToTexture = "assets/planetTextures/asteroid.jpg";
  // mass and radius of typical medium asteroid

  if (obj) {

    obj->setName("Asteroid");
    obj->setScale(irr::core::vector3df(size, size, size));

    if (driver) {

      irr::video::ITexture *texture = driver->getTexture(pathToTexture);

      obj->setMaterialTexture(0, texture);

      obj->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
  }
}

void Asteroid::drawPlanet(irr::video::IVideoDriver *driver) {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));

  orbit.drawOrbit(orbitedPlanet, driver);
}
