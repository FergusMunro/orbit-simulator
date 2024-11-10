#pragma once

#include "main/Planet.hpp"

class Star : public Planet {

public:
  Star(const Vector &_position, const Vector &_velocity);
  void drawPlanet() override;
  int getSize();

private:
  int size;
};
