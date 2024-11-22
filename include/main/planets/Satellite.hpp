#pragma once

#include "main/Planet.hpp"

class Satellite : public Planet {

public:
  Satellite(const Vector &_position, const Vector &_velocity,
            irr::scene::ISceneManager *smgr);
  void drawPlanet() override;
  __float128 getSize();

private:
  __float128 size;
  irr::scene::ISceneNode *obj = nullptr;
};
