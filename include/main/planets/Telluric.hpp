#pragma once

#include "main/Planet.hpp"

class Telluric : public Planet {

public:
  Telluric(const Vector &_position, const Vector &_velocity);
  void drawPlanet() override;
  int getSize();

private:
  int size;
};
