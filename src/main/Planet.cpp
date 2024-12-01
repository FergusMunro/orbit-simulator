#include "main/Planet.hpp"
#include "main/Orbit.hpp"
#include "main/Vector.hpp"

#include <irrlicht.h>

Planet::Planet(const Vector &_position, const Vector &_velocity)
    : position(_position), velocity(_velocity) {
  rotation = 0;
  pOrbitedPlanet = NULL;
}

Planet::~Planet() {}

void Planet::updateRotation() {
  rotation += rotation_rate;

  if (rotation >= 360) {
    rotation -= 360;
  }
  // to ensure that rotation is between 0 and 359
}

// getters and setters
__float128 Planet::getMass() const { return mass; }
void Planet::setMass(__float128 _mass) { mass = _mass; }
Vector Planet::getPosition() const { return position; }
void Planet::setPosition(const Vector &_position) { position = _position; }
Vector Planet::getVelocity() const { return velocity; }
void Planet::setVelocity(const Vector &_velocity) { velocity = _velocity; }
__float128 Planet::getSize() const { return size; }

void Planet::setOrbitedPlanet(Planet *planet) { pOrbitedPlanet = planet; }
Planet *Planet::getOrbitedPlanet() const { return pOrbitedPlanet; }
