#pragma once

#include "main/Vector.hpp"
class Planet;

class Orbit {
public:
  // methods

  // mathematical functions
  Vector convertToVelocity(const Planet &orbitedPlanet);
  Vector convertFromVelocity(const Vector &position, const Vector &velocity,
                             const Planet &orbitedPlanet);

  // other methods
  void drawOrbit(const Planet &orbitedPlanet);
  void toggleKeplersFirst();
  void toggleKeplersSecond();
  void toggleConstantSweeping();

  Orbit(const Vector &_position, const Vector &_velocity,
        Planet &orbitedPlanet);

  Orbit(int _angularMomentum, int _inclination, double _eccentricity,
        int _rightAscension, int _argp, int _trueanomaly);

private:
  // orbital elements

  int angularMomentum;
  int inclination;
  double eccentricity;
  int rightAscension;
  int argp;
  int trueanomaly;

  // other attributes

  bool keplersFirst;
  int keplersSecond;
  int sweepWidth;
};
