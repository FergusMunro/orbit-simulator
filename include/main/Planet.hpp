#pragma once

#include "main/Orbit.hpp"
#include "main/Vector.hpp"
#include <string>

#include <irrlicht.h>

class Planet {

public:
  // methods

  virtual void drawPlanet() = 0;
  void updateRotation();

  // Getters and Setters

  __float128 getMass();
  void setMass(__float128 _mass);
  Vector getPosition();
  void setPosition(Vector &_position);
  Vector getVelocity();
  void setVelocity(Vector &_velocity);

  void setOrbitedPlanet(Planet *planet);
  Planet *getOrbitedPlanet();

  // constructor
  Planet(const Vector &position, const Vector &velocity);
  // destructor
  ~Planet();

protected:
  // attributes

  __float128 mass;
  Orbit orbit;
  Vector position;
  Vector velocity;
  int rotation;
  int rotation_rate;
  std::string pathToTexture;

  Planet *pOrbitedPlanet;
};
