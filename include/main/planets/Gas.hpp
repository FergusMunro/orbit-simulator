#pragma once

#include "main/Planet.hpp"

class Gas : public Planet {

public:
  Gas(const Vector &_position, const Vector &_velocity,
      irr::scene::ISceneManager *smgr);
  void drawPlanet() override;
  __float128 getSize();

private:
  __float128 size;
  irr::scene::ISceneNode *obj = nullptr;
};
