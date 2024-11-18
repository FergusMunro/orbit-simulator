#pragma once

#include "main/Planet.hpp"
#include <forward_list>
#include <memory>

class PlanetManager {
public:
  // methods

  void const drawPlanets();
  void updatePositions();

  void addPlanet(std::unique_ptr<Planet> planetToAdd);
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

  Vector const calculateGravitationalAcceleration(const Planet &planet1,
                                                  const Planet &planet2);
  double const calculateGravitationalEnergy(const Planet &planet1,
                                            const Planet &planet2);
  bool const areIntersecting(const Planet &planet1, const Planet &planet2);
};
