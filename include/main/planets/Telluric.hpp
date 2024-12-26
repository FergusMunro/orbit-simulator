#pragma once

#include "main/Planet.hpp"

class Telluric : public Planet {

public:
  Telluric(const Vector &_position, const Vector &_velocity,
           irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);
  void drawPlanet() override;
};
