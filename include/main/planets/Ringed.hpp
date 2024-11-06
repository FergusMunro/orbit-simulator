#pragma once

#include "main/Planet.hpp"

class Ringed : public Planet {

public:
  Ringed();
  void drawPlanet() override;
  int getSize();

private:
  int size();

  void drawRings();
};
