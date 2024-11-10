#pragma once

#include "main/Planet.hpp"

class Ringed : public Planet {

public:
  Ringed(const Vector &_position, const Vector &_velocity);
  void drawPlanet() override;
  int getSize();

private:
  int size;

  void drawRings();
};
