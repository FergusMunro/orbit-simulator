#pragma once

#include "main/Planet.hpp"
#include <forward_list>
#include <memory>

class PlanetManager {
public:
  // methods

  void drawPlanets() const;
  void updatePositions();

  void addPlanet(Vector _position, Vector _velocity,
                 irr::scene::ISceneManager *smgr);
  void removePlanet(Planet &planetToRemove);
  void removeAll();
  void setTimeSpeed(int _timeSpeed);

  // constructor
  PlanetManager();

private:
  // linked list containing planets

  std::forward_list<std::unique_ptr<Planet>> planets;

  int timeSpeed;

  // private methods

  Vector calculateGravitationalAcceleration(const Planet &planet1,
                                            const Planet &planet2) const;
  double calculateGravitationalEnergy(const Planet &planet1,
                                      const Planet &planet2) const;
  bool areIntersecting(const Planet &planet1, const Planet &planet2) const;
};
