#pragma once

#include "main/Planet.hpp"

class Asteroid : public Planet {

public:
  Asteroid(const Vector &_position, const Vector &_velocity);
  void drawPlanet() override;
  __float128 getSize();

private:
  __float128 size;
};
