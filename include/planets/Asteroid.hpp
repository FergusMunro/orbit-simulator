#pragma once

#include "Planet.hpp"

class Asteroid : public Planet {

public:
  Asteroid();
  void drawPlanet() override;
  int getSize();

private:
  int size();
};
