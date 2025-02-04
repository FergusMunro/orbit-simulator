#include "main/planets/Star.hpp"
#include "main/Planet.hpp"
#include "vector3d.h"
#include <cmath>
#include <irrlicht.h>

Star::Star(const Vector &_position, const Vector &_velocity,
           irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver)
    : Planet(_position, _velocity, smgr, driver) {

  size = 600;
  mass = 1e6;
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/star.jpg";

  // based off sun

  if (obj) {

    obj->setName("Star");
    obj->setScale(irr::core::vector3df(size, size, size));
    if (driver) {

      irr::video::ITexture *texture = driver->getTexture(pathToTexture);

      obj->setMaterialTexture(0, texture);

      obj->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
  }
}

void Star::drawPlanet(irr::video::IVideoDriver *driver) {
  obj->setPosition(irr::core::vector3df(position.x, position.y, position.z));
}

void Star::setInclination(double _inclination) {}
double Star::getInclination() {
  return 0.01; // avoid return 0 as this causes many errors
}

void Star::setEccentricity(double _eccentricity) {}
double Star::getEccentricity() { return 0.01; }

void Star::setRadius(double _radius) {}

double Star::getRadius() { return 0.01; }
