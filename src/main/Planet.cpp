#include "main/Planet.hpp"
#include "main/Orbit.hpp"
#include "main/Vector.hpp"

Planet::Planet(const Vector &_position, const Vector &_velocity)
    : position(_position), velocity(_velocity) {
  rotation = 0;
  pOrbitedPlanet = NULL;
}

void Planet::updateRotation() {
  rotation += rotation_rate;

  if (rotation >= 360) {
    rotation -= 360;
  }
  // to ensure that rotation is between 0 and 359
}

// getters and setters
int Planet::getMass() { return mass; }
void Planet::setMass(int _mass) { mass = _mass; }
Vector Planet::getPosition() { return position; }
void Planet::setPosition(Vector &_position) { position = _position; }
Vector Planet::getVelocity() { return velocity; }
void Planet::setVelocity(Vector &_velocity) { velocity = _velocity; }

void Planet::setOrbitedPlanet(Planet *planet) { pOrbitedPlanet = planet; }
