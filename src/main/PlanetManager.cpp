#include "main/PlanetManager.hpp"
#include <memory>

PlanetManager::PlanetManager() {} // constructor doesn't need to do anything

void PlanetManager::addPlanet(std::unique_ptr<Planet> planetToAdd) {
  planets.push_front(std::move(planetToAdd));
}

void PlanetManager::removePlanet(Planet &planetToRemove) {
  // TODO
}

void PlanetManager::removeAll() {
  // TODO
}

void PlanetManager::updatePositions() {
  if (!planets.empty()) {

    for (const auto &planetPtr : planets) {
    }
  }
}

void const PlanetManager::drawPlanets() {
  // TODO
}

void PlanetManager::setTimeSpeed(int _timeSpeed) {

  if (_timeSpeed < 0) {
    // do nothing
  } else {
    timeSpeed = _timeSpeed;
  }
}

Vector const
PlanetManager::calculateGravitationalAcceleration(const Planet &planet1,
                                                  const Planet &planet2) {
  // TODO
  return Vector(0, 0, 0);
}
double const
PlanetManager::calculateGravitationalEnergy(const Planet &planet1,
                                            const Planet &planet2) {
  // TODO
  return 0;
}

bool const PlanetManager::areIntersecting(const Planet &planet1,
                                          const Planet &planet2) {
  return false;
}
