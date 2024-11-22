#include "main/PlanetManager.hpp"
#include "main/planets/Asteroid.hpp"
#include <memory>

PlanetManager::PlanetManager() {} // constructor doesn't need to do anything

void PlanetManager::addPlanet(Vector _position, Vector _velocity,
                              irr::scene::ISceneManager *smgr) {
  planets.push_front(
      std::make_unique<Asteroid>(Asteroid(_position, _velocity, smgr)));
  // basic version can only add asteroids
}

void PlanetManager::removePlanet(Planet &planetToRemove) {
  // TODO
}

void PlanetManager::removeAll() {

  if (!planets.empty()) {

    for (auto &planet : planets) {
      planet.reset();
    }
  }

  planets.clear();
}

void PlanetManager::updatePositions() {
  if (!planets.empty()) {

    for (const auto &planet : planets) {
      Vector p = planet->getPosition() + planet->getVelocity();
      planet->setPosition(p);
    }
  }
}

void const PlanetManager::drawPlanets() {
  if (!planets.empty()) {

    for (const auto &planet : planets) {
      planet->drawPlanet();
    }
  }
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
