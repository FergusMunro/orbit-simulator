#include "main/PlanetManager.hpp"
#include "main/Macros.hpp"

#include "main/Planet.hpp"
#include "main/planets/Asteroid.hpp"
#include "main/planets/Comet.hpp"
#include "main/planets/Gas.hpp"
#include "main/planets/Ringed.hpp"
#include "main/planets/Star.hpp"
#include "main/planets/Telluric.hpp"

#include <cmath>
#include <memory>

PlanetManager::PlanetManager() {
  timeSpeed = 1.0;
} // constructor doesn't need to do anything

std::weak_ptr<irr::scene::ISceneNode>
PlanetManager::addPlanet(const Vector &_position, const Vector &_velocity,
                         irr::scene::ISceneManager *smgr,
                         irr::video::IVideoDriver *driver, int type) {

  switch (type) {
  case _Asteroid:
    planets.push_front(
        std::make_unique<Asteroid>(_position, _velocity, smgr, driver));
    break;
  case _Comet:
    planets.push_front(
        std::make_unique<Comet>(_position, _velocity, smgr, driver));
    break;
  case _Gas:
    planets.push_front(
        std::make_unique<Gas>(_position, _velocity, smgr, driver));
    break;
  case _Ringed:
    planets.push_front(
        std::make_unique<Ringed>(_position, _velocity, smgr, driver));
    break;
  case _Star:
    planets.push_front(
        std::make_unique<Star>(_position, _velocity, smgr, driver));
    break;
  case _Telluric:
    planets.push_front(
        std::make_unique<Telluric>(_position, _velocity, smgr, driver));
    break;
  }
  return (**planets.begin()).getSceneNodePtr();
}

void PlanetManager::removePlanet(Planet &planetToRemove) {
  // TODO
}

void PlanetManager::removeAll() { planets.clear(); }

void PlanetManager::updatePositions(double timeDelta) {
  if (!planets.empty()) {
    // if didn't check and planets was empty, would crash

    // handle collions section

    auto prev1 = planets.before_begin();
    auto planet1 = planets.begin();
    while (planet1 != planets.end()) {

      auto prev2 = planets.before_begin();

      auto planet2 = planets.begin();

      int p1delete = 0;

      while (planet2 != planets.end()) {

        if (areIntersecting(**planet1, **planet2) && planet1 != planet2) {
          if ((**planet1).getMass() >= (**planet2).getMass()) {
            planet2->reset();
            planet2 = planets.erase_after(prev2);
          } else {
            p1delete = 1;
            break;
          }
        } else {
          prev2 = planet2;
          planet2++;
        }
      }
      if (p1delete) {
        planet1->reset();
        planet1 = planets.erase_after(prev1);
      } else {

        prev1 = planet1;
        planet1++;
      }
    }

    // although I could have put them in the same list, the collisions section
    // is quite complicated since it has to operate on a linked list that has
    // elements being deleted from it. For this reason it is just simpler to do
    // two separate iterations, one for the intersections and one for everything
    // else. Also this means I can use the built in iterators which are much
    // nicer than manually using pointers like before

    // handle acceleration section

    Vector acceleration = Vector(0, 0, 0);

    for (auto &planet : planets) {

      acceleration.x = 0;
      acceleration.y = 0;
      acceleration.z = 0;

      for (auto &planetWithGravity : planets) {

        if (planet != planetWithGravity) {
          acceleration = acceleration + calculateGravitationalAcceleration(
                                            *planet, *planetWithGravity);
        }
      }

      planet->setVelocity(planet->getVelocity() +
                          acceleration * timeDelta * timeSpeed);
      planet->setPosition(planet->getPosition() +
                          planet->getVelocity() * timeDelta * timeSpeed);
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
