#pragma once

#include "main/Orbit.hpp"
#include "main/Vector.hpp"
#include <string>

class Planet {

public:
  // methods

  virtual void drawPlanet() = 0;
  void updateRotation();

  // Getters and Setters

  int getMass();
  void setMass(int _mass);
  Vector getPosition();
  void setPosition(Vector &_position);
  Vector getVelocity();
  void setVelocity(Vector &_velocity);

  void setOrbitedPlanet(Planet *planet);
  Planet *getOrbitedPlanet();

  // constructors
  Planet(const Vector &position, const Vector &velocity);

protected:
  // attributes

  long double mass;
  Orbit orbit;
  Vector position;
  Vector velocity;
  int rotation;
  int rotation_rate;
  std::string pathToTexture;

  Planet *pOrbitedPlanet;
};
