#pragma once

#include "main/Planet.hpp"

class Asteroid : public Planet {

public:
  Asteroid(const Vector &_position, const Vector &_velocity,
           irr::scene::ISceneManager *smgr);
  void drawPlanet() override;

private:
};
