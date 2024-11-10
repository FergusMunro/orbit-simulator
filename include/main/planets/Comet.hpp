#pragma once

#include "main/Planet.hpp"

class Comet : public Planet {

public:
  Comet(const Vector &_position, const Vector &_velocity);
  void drawPlanet() override;
  int getSize();

private:
  int size;

  void drawTrail();
};
