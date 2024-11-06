#include "main/Orbit.hpp"

// constructor for passing velocity and position directly
Orbit::Orbit(const Vector &_position, const Vector &_velocity,
             Planet &orbitedPlanet) {

  convertFromVelocity(_position, _velocity, orbitedPlanet);
}

// constructor for orbital parameters, just a big initialiser list
Orbit::Orbit(int _angularMomentum, int _inclination, double _eccentricity,
             int _rightAscension, int _argp, int _trueanomaly)
    : angularMomentum(_angularMomentum), inclination(_inclination),
      eccentricity(_eccentricity), rightAscension(_rightAscension), argp(_argp),
      trueanomaly(_trueanomaly) {}

void Orbit::drawOrbit(const Planet &orbitedPlanet) {
  // TODO
}

void Orbit::toggleKeplersFirst() {
  if (keplersFirst == true) {
    keplersFirst = false;
  } else {
    keplersFirst = true;
  }
}

void Orbit::toggleKeplersSecond() {
  if (keplersSecond % 2 == 0) {
    keplersSecond /= 2;
  } else {
    keplersSecond *= 2;
  }
}

void Orbit::toggleConstantSweeping() {
  if (keplersSecond % 3 == 0) {
    keplersSecond /= 3;
  } else {
    keplersSecond *= 3;
  }
}
