#include "main/Orbit.hpp"
#include "SColor.h"
#include "main/Macros.hpp"
#include "main/Planet.hpp"
#include "vector3d.h"

#include <algorithm>
#include <cmath>
#include <forward_list>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

// constructor for passing velocity and position directly
Orbit::Orbit(const Vector &_position, const Vector &_velocity,
             std::weak_ptr<Planet> orbitedPlanet) {

  stateVectorsToOrbitalElements(_position, _velocity, orbitedPlanet);
}

// constructor for orbital parameters, just a big initialiser list
Orbit::Orbit(double _angularMomentum, double _inclination,
             double _rightAscension, double _eccentricity, double _argp,
             double _trueanomaly)
    : angularMomentum(_angularMomentum), inclination(_inclination),
      eccentricity(_eccentricity), rightAscension(_rightAscension), argp(_argp),
      trueanomaly(_trueanomaly) {}

void Orbit::drawOrbit(std::weak_ptr<Planet> orbitedPlanet,
                      irr::video::IVideoDriver *driver) {

  std::shared_ptr<Planet> p = orbitedPlanet.lock();

  if (p) {

    std::forward_list<irr::core::vector3df> points;
    // linked list containing all the points of the ellipse

    double storedTrueAnomaly = trueanomaly;
    // we are going to vary the trueanomaly to draw all the points of the orbit
    // using the convertovelocity function, so we need to store the old value to
    // set it back at the end

    Vector pos = Vector(0, 0, 0);

    for (int i = 0; i < ORBITAL_ACCURARCY; i++) {

      trueanomaly = i * 2 * CONST_PI / ORBITAL_ACCURARCY;
      // we change the true anomaly around 2pi to represent all positions in
      // orbit

      pos = orbitalElementsToStateVectors(orbitedPlanet).position;

      points.push_front(irr::core::vector3df(pos.x, pos.y, pos.z));
    }

    auto point = points.begin()++;
    auto prev = points.begin();

    // since we are manually drawing the lines we need to adjust the material to
    // be right for drawing lines. we need to do this every time we draw as
    // other functions will change it

    irr::video::SMaterial material;
    material.Lighting = false;
    driver->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);

    driver->setMaterial(material);

    // we need to now manually draw these points, by drawing a line between
    // adjacent points

    while (point != points.end()) {

      driver->draw3DLine(*prev, *point, irr::video::SColor(255, 255, 255, 255));

      prev = point;
      point++;
    }

    // draw line between prev and start as otherwise there would be a gap
    driver->draw3DLine(*prev, *points.begin(),
                       irr::video::SColor(255, 255, 255, 255));

    // set back the old value of trueanomaly
    trueanomaly = storedTrueAnomaly;

  } else {
    std::cerr << "error with weak pointer not locking\n";
  }
}

pos_and_vel
Orbit::orbitalElementsToStateVectors(std::weak_ptr<Planet> orbitedPlanet) {

  std::shared_ptr<Planet> p = orbitedPlanet.lock();

  if (p) {
    double mu = CONST_G * p->getMass();

    Vector r_vec = Vector(cos(trueanomaly), sin(trueanomaly), 0);

    r_vec = r_vec * (pow(angularMomentum, 2) / mu) *
            (1 / (1 + eccentricity * cos(trueanomaly)));

    // apply formula for radius of orbit, and take cos and sin of it to find
    // components in x and y directions in perefocal frame

    Vector v_vec =
        Vector(-sin(trueanomaly), eccentricity + cos(trueanomaly), 0);

    v_vec = v_vec * (mu / angularMomentum);

    // apply formula for velocity in perefocal frame

    glm::mat3 R1 =
        glm::mat3(glm::vec3(cos(-argp), -sin(-argp), 0),
                  glm::vec3(sin(-argp), cos(-argp), 0), glm::vec3(0, 0, 1));

    glm::mat3 R2 = glm::mat3(
        glm::vec3(1, 0, 0), glm::vec3(0, cos(-inclination), -sin(-inclination)),
        glm::vec3(0, sin(-inclination), cos(-inclination)));

    glm::mat3 R3 =
        glm::mat3(glm::vec3(cos(-rightAscension), -sin(-rightAscension), 0),
                  glm::vec3(sin(-rightAscension), cos(-rightAscension), 0),
                  glm::vec3(0, 0, 1));
    // create 3 rotation matrixices around euler angles of argument of
    // periapsis, inclination and right ascension of ascending node

    // convert them to a vector that supports matrix multiplcation
    glm::vec3 position = glm::vec3(r_vec.x, r_vec.y, r_vec.z);
    glm::vec3 velocity = glm::vec3(v_vec.x, v_vec.y, v_vec.z);

    position = R3 * R2 * R1 * position;
    velocity = R3 * R2 * R1 * velocity;
    // perform the rotations to turn relative position/velocity into absolute

    // convert them back to vector that the rest of the system can support, and
    // add the position and velocity of the orbited planet

    Vector _position =
        Vector(position.x, position.y, position.z) + p->getPosition();

    Vector _velocity =
        Vector(velocity.x, velocity.y, velocity.z) + p->getVelocity();

    return pos_and_vel(_position, _velocity);
  } else {
    std::cerr << "error with weak pointer not locking\n";
    return pos_and_vel(Vector(0, 0, 0), Vector(0, 0, 0));
  }
}

void Orbit::stateVectorsToOrbitalElements(const Vector &_position,
                                          const Vector &_velocity,
                                          std::weak_ptr<Planet> orbitedPlanet) {
  std::shared_ptr<Planet> p = orbitedPlanet.lock();
  if (p) {
    double mu = CONST_G * p->getMass();

    Vector position = _position - p->getPosition();
    Vector velocity = _velocity - p->getVelocity();

    double r = position.magnitude();
    double v = velocity.magnitude();

    double v_r = Vector::dot(position.normalise(), velocity);
    double v_p = sqrt((pow(v, 2) - pow(v_r, 2)));

    Vector h_vec = Vector::cross(position, velocity);
    angularMomentum = h_vec.magnitude();

    inclination = acos((double)h_vec.z / angularMomentum);
    Vector K = Vector(0, 0, 1);

    Vector N_vec = Vector::cross(K, h_vec);

    double N = N_vec.magnitude();

    rightAscension = acos(std::clamp((double)N_vec.x / N, -1.0, 1.0));
    if (N_vec.y < 0) {
      rightAscension = 2 * CONST_PI - rightAscension;
    }

    Vector e_vec =
        (Vector::cross(velocity, h_vec) * (1 / mu)) - (position.normalise());

    eccentricity = e_vec.magnitude();

    argp = acos(
        std::clamp((double)Vector::dot(N_vec, e_vec) * (1 / (N * eccentricity)),
                   -1.0, 1.0));

    if (e_vec.z < 0) {
      argp = 2 * CONST_PI - argp;
    }

    trueanomaly = acos(
        std::clamp((double)Vector::dot(position.normalise(), e_vec.normalise()),
                   -1.0, 1.0));

    if (v_r < 0) {
      trueanomaly = 2 * CONST_PI - trueanomaly;
    }
  } else {
    std::cerr << "error with weak pointer not locking\n";
  }
}

void Orbit::toggleKeplersFirst() {
  if (keplersFirst == true) {
    keplersFirst = false;
  } else {
    keplersFirst = true;
  }
}

void Orbit::toggleKeplersSecond() {
  if (keplersSecond % 2 == 0) {
    keplersSecond /= 2;
  } else {
    keplersSecond *= 2;
  }
}

void Orbit::toggleConstantSweeping() {
  if (keplersSecond % 3 == 0) {
    keplersSecond /= 3;
  } else {
    keplersSecond *= 3;
  }
}
