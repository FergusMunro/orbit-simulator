#pragma once

#include "main/Planet.hpp"

class Star : public Planet {

public:
  Star(const Vector &_position, const Vector &_velocity,
       irr::scene::ISceneManager *smgr);
  void drawPlanet() override;

private:
  irr::scene::ISceneNode *obj = nullptr;
};
