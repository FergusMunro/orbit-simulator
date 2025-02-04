#pragma once

#include "main/Planet.hpp"

class Star : public Planet {

public:
  Star(const Vector &_position, const Vector &_velocity,
       irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);
  void drawPlanet(irr::video::IVideoDriver *driver) override;

  double getInclination() override;
  void setInclination(double _inclination) override;

  double getEccentricity() override;
  void setEccentricity(double _eccentricity) override;

  double getRadius() override;
  void setRadius(double _radius) override;
};
