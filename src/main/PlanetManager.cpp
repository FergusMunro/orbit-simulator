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
#include <iostream>
#include <memory>

PlanetManager::PlanetManager() {
  timeSpeed = 1.0;
} // constructor doesn't need to do anything

std::weak_ptr<irr::scene::ISceneNode>
PlanetManager::addPlanet(const Vector &_position, const Vector &_velocity,
                         irr::scene::ISceneManager *smgr,
                         irr::video::IVideoDriver *driver, int type) {

  // switch statement to add different planet based on provided type
  switch (type) {
  case _Asteroid:
    planets.push_front(
        std::make_shared<Asteroid>(_position, _velocity, smgr, driver));
    break;
  case _Comet:
    planets.push_front(
        std::make_shared<Comet>(_position, _velocity, smgr, driver));
    break;
  case _Gas:
    planets.push_front(
        std::make_shared<Gas>(_position, _velocity, smgr, driver));
    break;
  case _Ringed:
    planets.push_front(
        std::make_shared<Ringed>(_position, _velocity, smgr, driver));
    break;
  case _Star:
    planets.push_front(
        std::make_shared<Star>(_position, _velocity, smgr, driver));
    break;
  case _Telluric:
    planets.push_front(
        std::make_shared<Telluric>(_position, _velocity, smgr, driver));
    break;
  }
  // return a weak pointer to the scene node pointer. this is stored by the gui
  // and used to find which planet is clicked on by linking the planet to its
  // scene node pointer, however we need to give it the weak pointer first to
  // make sure it doesn't cause crashes if one gets deleted
  return (**planets.begin()).getSceneNodePtr();
}

void PlanetManager::removeAll() { planets.clear(); }

void PlanetManager::updatePositions(double timeDelta) {
  if (!planets.empty()) {
    // if didn't check and planets was empty, would crash

    // handle collions section

    auto prev1 =
        planets.before_begin(); // need to keep track of previous as when
                                // wanting to delete current node, need to
                                // previous node since is a singly linked list
    auto planet1 = planets.begin();
    while (planet1 != planets.end()) {

      auto prev2 = planets.before_begin();

      auto planet2 = planets.begin();

      int p1delete = 0;

      while (planet2 != planets.end()) {
        // second loop - same as before

        if (areIntersecting(**planet1, **planet2) && planet1 != planet2) {
          // if they are intersecting
          if ((**planet1).getMass() >= (**planet2).getMass()) {
            planet2->reset();
            planet2 = planets.erase_after(prev2);
          } else {
            p1delete = 1; // cant delete planet 1 straight away, as this would
                          // cause crash as we need to iterate over planet2
                          // first and compare with planet 1 which if planet 1
                          // is deleted would cause crash
            break;
          }
        } else {
          prev2 = planet2;
          planet2++;
        }
      }
      if (p1delete) {
        // delete first planet
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
    Vector currentAcceleration = Vector(0, 0, 0);
    std::weak_ptr<Planet> orbitedPlanet;

    double energy = 0;

    double max;

    for (auto &planet : planets) {
      // since no deleting is needed here, can use simpler iterator

      acceleration.x = 0;
      acceleration.y = 0;
      acceleration.z = 0;

      max = 0;

      energy = 0;

      for (auto &planetExertingGravity : planets) {

        if (planet != planetExertingGravity) {
          // don't have planet apply gravity to itself

          // caluclate acceleration
          currentAcceleration = calculateGravitationalAcceleration(
              *planet, *planetExertingGravity);
          acceleration = acceleration + currentAcceleration;

          // keep track of maximum acceleration for finding orbited planet
          if (currentAcceleration.magnitude() > max) {
            max = currentAcceleration.magnitude();
            orbitedPlanet = planetExertingGravity;
          }

          // calculate energy
          energy +=
              calculateGravitationalEnergy(*planet, *planetExertingGravity);
        }
      }

      // update velocity, position, orbited planet and energy for this planet
      planet->setVelocity(planet->getVelocity() +
                          acceleration * timeDelta * timeSpeed);
      planet->setPosition(planet->getPosition() +
                          planet->getVelocity() * timeDelta * timeSpeed);
      planet->setOrbitedPlanet(orbitedPlanet);
      planet->setGravitationalEnergy(energy);

      // update orbital characteristics based on new information
      planet->updateOrbit();
    }
  }
}

void PlanetManager::drawPlanets(irr::video::IVideoDriver *driver) const {
  if (!planets.empty()) { // check planets not empty as otherwise would crash

    for (auto &planet : planets) {
      planet->drawPlanet(driver);
    }
  }
}

void PlanetManager::setTimeSpeed(int _timeSpeed) {

  if (_timeSpeed < 0) {
    // do nothing - stops negative timespeed
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

  Vector distance = planet2.getPosition() - planet1.getPosition();
  // find distance

  return -1 * CONST_G * planet1.getMass() * planet2.getMass() /
         distance.magnitude();
  // apply and return formula
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

std::weak_ptr<Planet> PlanetManager::getPlanetFromSceneNode(
    std::weak_ptr<irr::scene::ISceneNode> sceneNode) {
  // this function is a linear search to return a planet based on its scene node
  // pointer, which is given as a parameter

  for (auto &planet : planets) { // iterate over planets

    if (planet->getSceneNodePtr().lock() && sceneNode.lock()) {

      // if scene node raw pointer for input and planet are equal, must be
      // planet to return
      // otherwise keep searching
      if (planet->getSceneNodePtr().lock().get() == sceneNode.lock().get()) {
        return planet;
      }
    }
  }
  std::cerr << "error: planet not found for scene node\n";
  // just return a random planet to keep the compiler happy, this code should
  // never run
  return std::make_shared<Ringed>(Vector(0, 0, 0), Vector(0, 0, 0), nullptr,
                                  nullptr);
}

void PlanetManager::removePlanet(std::weak_ptr<Planet> planetToRemove) {

  if (planetToRemove.lock()) {
    // check planet not already deleted - if it is nothing needs to be done

    Planet *p = planetToRemove.lock().get();
    // get raw pointer for comparison later

    auto prev = planets.before_begin();
    auto planet = planets.begin();
    // previous planet needed in iteration as linked list is forward only, so
    // can only remove element if have previous node

    while (planet != planets.end()) {
      // iterate over planets list

      if (planet->get() == p) {
        // if they have same pointer we have found planet to remove, so remove
        // it
        planets.erase_after(prev);
        return;
      }

      prev = planet;
      planet++;
    }
  }
}
