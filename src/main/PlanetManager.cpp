#include "main/PlanetManager.hpp"
#include "main/planets/Asteroid.hpp"

#include "main/Macros.hpp"
#include <cmath>
#include <memory>

PlanetManager::PlanetManager() {
  timeSpeed = 1;
} // constructor doesn't need to do anything

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
    // if didn't check and planets was empty, would crash

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
  // the order of subraction matters as if p1 - p2 then force would be repulsive
  // not attractive
  Vector d = planet2.getPosition() - planet1.getPosition();

  // applies simplified formula of newtons law of gravitation

  double acceleration = (CONST_G * planet2.getMass()) / pow(d.magnitude(), 2);

  // acceleration scalar multiplied by unit vector in direction of attracting
  // planet

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
  Vector d = planet1.getPosition() - planet2.getPosition();

  // works out if distance between planet's centres is less than sum of planet's
  // radii. If so, then must be intersecting

  if (d.magnitude() <= planet1.getSize() + planet2.getSize()) {
    return true;
  } else {
    return false;
  }
}
