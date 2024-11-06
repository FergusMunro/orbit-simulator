#pragma once

#include "main/Planet.hpp"

class Telluric : public Planet {

public:
  Telluric();
  void drawPlanet() override;
  int getSize();

private:
  int size();
};
