#pragma once

#include "main/Planet.hpp"

class Satellite : public Planet {

public:
  Satellite();
  void drawPlanet() override;
  int getSize();

private:
  int size();
};
