#include "main/Orbit.hpp"
#include "main/Macros.hpp"
#include "main/Planet.hpp"

#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

// constructor for passing velocity and position directly
Orbit::Orbit(const Vector &_position, const Vector &_velocity,
             std::weak_ptr<Planet> orbitedPlanet) {

  convertFromVelocity(_position, _velocity, orbitedPlanet);
}

// constructor for orbital parameters, just a big initialiser list
Orbit::Orbit(double _angularMomentum, double _inclination,
             double _rightAscension, double _eccentricity, double _argp,
             double _trueanomaly)
    : angularMomentum(_angularMomentum), inclination(_inclination),
      eccentricity(_eccentricity), rightAscension(_rightAscension), argp(_argp),
      trueanomaly(_trueanomaly) {}

void Orbit::drawOrbit(std::weak_ptr<Planet> orbitedPlanet) {

  std::shared_ptr<Planet> p = orbitedPlanet.lock();

  if (p) {

    double mu = CONST_G * p->getMass();

    double semiMajorAxis =
        (pow(angularMomentum, 2) / mu) / (1 - pow(eccentricity, 2));

    double semiMinorAxis = semiMajorAxis * sqrt(1 - pow(eccentricity, 2));
  } else {
    std::cerr << "error with weak pointer not locking\n";
  }
}

pos_and_vel Orbit::convertToVelocity(std::weak_ptr<Planet> orbitedPlanet) {

  std::shared_ptr<Planet> p = orbitedPlanet.lock();

  if (p) {
    double mu = CONST_G * p->getMass();

    Vector r_vec = Vector(cos(trueanomaly), sin(trueanomaly), 0);

    r_vec = r_vec * (pow(angularMomentum, 2) / mu) *
            (1 / (1 + eccentricity * cos(trueanomaly)));

    Vector v_vec =
        Vector(-sin(trueanomaly), eccentricity + cos(trueanomaly), 0);

    v_vec = v_vec * (mu / angularMomentum);

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

    // convert them to a vector that supports matrix multiplcation
    glm::vec3 position = glm::vec3(r_vec.x, r_vec.y, r_vec.z);
    glm::vec3 velocity = glm::vec3(v_vec.x, v_vec.y, v_vec.z);

    position = R3 * R2 * R1 * position;
    velocity = R3 * R2 * R1 * velocity;

    // convert them back to vector that i can return

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

void Orbit::convertFromVelocity(const Vector &_position,
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
