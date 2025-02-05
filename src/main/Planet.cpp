#include "main/Planet.hpp"
#include "main/Orbit.hpp"
#include "main/Vector.hpp"

#include <irrlicht.h>

Planet::Planet(const Vector &_position, const Vector &_velocity,
               irr::scene::ISceneManager *smgr,
               irr::video::IVideoDriver *driver)
    : position(_position), velocity(_velocity),
      orbit(_position.x, _position.y, _position.z, _velocity.x, _velocity.y,
            _velocity.z) {

  rotation = 0;

  if (smgr) { // check if smgr is not null

    obj = std::shared_ptr<irr::scene::ISceneNode>(
        smgr->addSphereSceneNode(1), [](irr::scene::ISceneNode *ptr) {
          if (ptr) {
            ptr->remove();
          }
        });

    // this code adds a custom deleter to our smart pointer, which means
    // we no longer need to destroy planet's ascociated scene node when we
    // delete planet, as this will do it for us when it goes out of scope

    // it works by passing a second parameter of a function to the making of the
    // shared poitner which does the deleting

    if (obj) { // check obj initialised correctly
      obj->setPosition(
          irr::core::vector3df(position.x, position.y, position.z));
    }
  }
}

Planet::~Planet() {}

void Planet::updateRotation() {
  rotation += rotation_rate;

  if (rotation >= 360) {
    rotation -= 360;
  }
  // to ensure that rotation is between 0 and 359
}

void Planet::updateOrbit() {
  orbit.stateVectorsToOrbitalElements(position, velocity, orbitedPlanet);
}

// getters and setters
__float128 Planet::getMass() const { return mass; }
void Planet::setMass(__float128 _mass) { mass = _mass; }
Vector Planet::getPosition() const { return position; }
void Planet::setPosition(const Vector &_position) { position = _position; }
Vector Planet::getVelocity() const { return velocity; }
void Planet::setVelocity(const Vector &_velocity) { velocity = _velocity; }
__float128 Planet::getSize() const { return size; }
std::weak_ptr<irr::scene::ISceneNode> Planet::getSceneNodePtr() {
  std::weak_ptr<irr::scene::ISceneNode> wk = obj;
  return wk;
  // the reason we can't return obj directly is because that would return a
  // shared poitner which is not what we want
}

void Planet::setOrbitedPlanet(std::weak_ptr<Planet> planet) {
  orbitedPlanet = planet;
}
std::weak_ptr<Planet> Planet::getOrbitedPlanet() const { return orbitedPlanet; }

double Planet::getRadius() { return orbit.getRadius(orbitedPlanet); }

void Planet::setRadius(double _radius) {
  orbit.setRadius(_radius, orbitedPlanet);
  pos_and_vel velpos = orbit.orbitalElementsToStateVectors(orbitedPlanet);
  position = velpos.position;
  velocity = velpos.velocity;
}

double Planet::getEccentricity() { return orbit.getEccentricity(); }

void Planet::setEccentricity(double _eccentricity) {
  orbit.setEccentricity(_eccentricity, orbitedPlanet);
  pos_and_vel velpos = orbit.orbitalElementsToStateVectors(orbitedPlanet);
  position = velpos.position;
  velocity = velpos.velocity;
}

double Planet::getInclination() { return orbit.getInclination(); }

void Planet::setInclination(double _inclination) {
  orbit.setInclination(_inclination);
  pos_and_vel velpos = orbit.orbitalElementsToStateVectors(orbitedPlanet);
  position = velpos.position;
  velocity = velpos.velocity;
}
