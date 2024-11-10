#pragma once

#include "main/Planet.hpp"

class Satellite : public Planet {

public:
  Satellite(const Vector &_position, const Vector &_velocity);
  void drawPlanet() override;
  int getSize();

private:
  int size;
};
