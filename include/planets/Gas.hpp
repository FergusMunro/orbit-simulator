#pragma once

#include "Planet.hpp"

class Gas : public Planet {

public:
  Gas();
  void drawPlanet() override;
  int getSize();

private:
  int size();
};
