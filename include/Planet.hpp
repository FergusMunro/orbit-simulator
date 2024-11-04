#pragma once

#include "Orbit.hpp"
#include "Vector.hpp"
#include <string>

class Planet {

public:
  // methods

  virtual void drawPlanet();
  void updateRotation();

  // Getters and Setters

  int getMass();
  void setMass(int _mass);
  Vector getPosition();
  void setPosition(Vector &_position);
  Vector getVelocity();
  void setVelocity(Vector &_velocity);

  // constructors
  Planet(const Vector &position, const Vector &velocity);

protected:
  // attributes

  int mass;
  Orbit orbit;
  Vector position;
  Vector velocity;
  int rotation;
  int rotation_rate;
  std::string pathToTexture;
};
