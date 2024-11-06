#pragma once

#include "main/Vector.hpp"
class Planet;

class Orbit {
public:
  // methods

  // mathematical functions
  Vector convertToVelocity(Planet &orbitedPlanet);
  Vector convertFromVelocity(Vector &position, Vector &velocity,
                             Planet &orbitedPlanet);

  // other methods
  void drawOrbit(Planet &orbitedPlanet);
  void toggleKeplersFirst();
  void toggleKeplersSecond();
  void toggleConstantSweeping();

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
