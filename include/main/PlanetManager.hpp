#pragma once

#include "IVideoDriver.h"
#include "main/Planet.hpp"
#include <forward_list>
#include <memory>

class PlanetManager {
public:
  // methods

  void drawPlanets() const;
  void updatePositions();
  std::weak_ptr<irr::scene::ISceneNode>
  addPlanet(const Vector &_position, const Vector &_velocity,
            irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
            int type);

  void removePlanet(Planet &planetToRemove);
  void removeAll();
  void setTimeSpeed(int _timeSpeed);

  // constructor
  PlanetManager();

private:
  // linked list containing planets

  std::forward_list<std::unique_ptr<Planet>> planets;

  float timeSpeed;

  // private methods

  Vector calculateGravitationalAcceleration(const Planet &planet1,
                                            const Planet &planet2) const;
  double calculateGravitationalEnergy(const Planet &planet1,
                                      const Planet &planet2) const;
  bool areIntersecting(const Planet &planet1, const Planet &planet2) const;
};
