#include "main/PlanetManager.hpp"
#include "main/planets/Asteroid.hpp"

#include "main/Macros.hpp"
#include <cmath>
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

void PlanetManager::removeAll() { planets.clear(); }

void PlanetManager::updatePositions() {
  if (!planets.empty()) {

    for (auto &planet : planets) {
      Vector p = planet->getPosition() + planet->getVelocity();
      planet->setPosition(p);
    }
  }
}

void PlanetManager::drawPlanets() const {
  if (!planets.empty()) {

    for (auto &planet : planets) {
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

Vector
PlanetManager::calculateGravitationalAcceleration(const Planet &planet1,
                                                  const Planet &planet2) const {
  Vector d = planet2.getPosition() - planet1.getPosition();

  double acceleration =
      (CONST_G * planet2.getMass() * timeSpeed) / pow(d.magnitude(), 2);

  return d.normalise() * acceleration;
}
double
PlanetManager::calculateGravitationalEnergy(const Planet &planet1,
                                            const Planet &planet2) const {
  // TODO
  return 0;
}

bool PlanetManager::areIntersecting(const Planet &planet1,
                                    const Planet &planet2) const {
  return false;
}
