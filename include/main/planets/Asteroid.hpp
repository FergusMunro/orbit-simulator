#pragma once

#include "main/Planet.hpp"

class Asteroid : public Planet {

public:
  Asteroid(const Vector &_position, const Vector &_velocity);
  void drawPlanet() override;
  int getSize();

private:
  int size;
};
