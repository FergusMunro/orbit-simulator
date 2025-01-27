#pragma once

#include "main/Vector.hpp"
#include <memory>
class Planet;

struct pos_and_vel {
  Vector position;
  Vector velocity;
  pos_and_vel(Vector _p, Vector _v) : position(_p), velocity(_v) {}
};

class Orbit {
public:
  // mathematical functions
  pos_and_vel convertToVelocity(std::weak_ptr<Planet> orbitedPlanet);
  void convertFromVelocity(const Vector &position, const Vector &velocity,
                           std::weak_ptr<Planet> orbitedPlanet);

  // other methods
  void drawOrbit(const Planet &orbitedPlanet);
  void toggleKeplersFirst();
  void toggleKeplersSecond();
  void toggleConstantSweeping();

  Orbit(const Vector &_position, const Vector &_velocity,
        std::weak_ptr<Planet> orbitedPlanet);

  Orbit(int _angularMomentum, int _inclination, double _eccentricity,
        int _rightAscension, int _argp, int _trueanomaly);

private:
  // orbital elements

  double angularMomentum;
  double inclination;
  double eccentricity;
  double rightAscension;
  double argp;
  double trueanomaly;

  // other attributes

  bool keplersFirst = false;
  int keplersSecond = 1;
  int sweepWidth = 1;
};
