#pragma once

#include "main/Planet.hpp"

class Gas : public Planet {

public:
  Gas(const Vector &_position, const Vector &_velocity,
      irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);
  void drawPlanet() override;
};
