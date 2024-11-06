#pragma once

#include "main/Planet.hpp"
#include <forward_list>

class PlanetManager {
public:
  // methods

  void const drawPlanets();
  void updatePositions();

  void addPlanet(Planet planetToAdd);
  void removePlanet(Planet &planetToRemove);
  void removeAll();
  void setTimeSpeed(int _timeSpeed);

  // constructor
  PlanetManager();

private:
  // linked list containing planets
  std::forward_list<Planet> planets;

  double timespeed;

  // private methods

  Vector const calculateGravitationalAcceleration(const Planet &planet1,
                                                  const Planet &planet2);
  Vector const calculateGravitationalEnergy(const Planet &planet1,
                                            const Planet &planet2);
  bool const areIntersecting(const Planet &planet1, const Planet &planet2);
};
