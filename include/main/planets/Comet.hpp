#pragma once

#include "main/Planet.hpp"

class Comet : public Planet {

public:
  Comet(const Vector &_position, const Vector &_velocity,
        irr::scene::ISceneManager *smgr);
  void drawPlanet() override;
  __float128 getSize();

private:
  __float128 size;

  void drawTrail();
  irr::scene::ISceneNode *obj = nullptr;
};
