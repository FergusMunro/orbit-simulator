#pragma once

#include "main/Planet.hpp"

class Gas : public Planet {

public:
  Gas(const Vector &_position, const Vector &_velocity);
  void drawPlanet() override;
  int getSize();

private:
  int size;
};
