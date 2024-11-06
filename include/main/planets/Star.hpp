#pragma once

#include "main/Planet.hpp"

class Star : public Planet {

public:
  Star();
  void drawPlanet() override;
  int getSize();

private:
  int size();
};
