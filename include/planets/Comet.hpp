#pragma once

#include "Planet.hpp"

class Comet : public Planet {

public:
  Comet();
  void drawPlanet() override;
  int getSize();

private:
  int size();

  void drawTrail();
};
