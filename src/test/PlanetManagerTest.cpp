#include "main/Macros.hpp"
#include "main/planets/Asteroid.hpp"
#include "main/planets/Star.hpp"
#include <iostream>
#define private public
#define protected public
/*
 * Basically, this changes all privates and protecteds to publics in the other
 * classes, which means that I can access them to test the code
 */

#include "catch.h"

#include "main/PlanetManager.hpp"
#include "main/Vector.hpp"
#include "main/planets/Telluric.hpp"
#include <cmath>
#include <memory>

TEST_CASE("planet Manager Tests") {
  PlanetManager pm;

  pm.addPlanet(Vector(0, 0, 0), Vector(0, 0, 0), nullptr, nullptr, _Telluric);

  SECTION("linked list test") {

    auto it = pm.planets.begin();

    REQUIRE((**it).getMass() == 100);
  }

  SECTION("gravitational acceleration test") {

    // TODO: fix this for new sets of values

    Telluric a1 = Telluric(Vector(4, 4, 4), Vector(0, 0, 0), nullptr, nullptr);

    Telluric a2 =
        Telluric(Vector(6, 11, 30), Vector(0, 0, 0), nullptr, nullptr);

    Vector acceleration = pm.calculateGravitationalAcceleration(a1, a2);

    REQUIRE_THAT(acceleration.magnitude(),
                 Catch::Matchers::WithinAbs(1371.74211, 0.01));

    REQUIRE_THAT(acceleration.x, Catch::Matchers::WithinAbs(101.611, 0.01));
    REQUIRE_THAT(acceleration.y, Catch::Matchers::WithinAbs(355.637, 0.01));
    REQUIRE_THAT(acceleration.z, Catch::Matchers::WithinAbs(1320.94, 0.01));
  }

  SECTION("intersection test") {

    Telluric a1 = Telluric(Vector(0, 0, 0), Vector(0, 0, 0), nullptr, nullptr);

    // Intersecting Position

    Telluric a2 = Telluric(Vector(50, 0, 0), Vector(0, 0, 0), nullptr, nullptr);

    REQUIRE(pm.areIntersecting(a1, a2));

    // Not intersecting position

    a2.setPosition(Vector(210, 0, 0));

    REQUIRE(!pm.areIntersecting(a1, a2));

    // Boundary - just touching - should count as intersection

    a2.setPosition(Vector(0, 0, 60));

    REQUIRE(pm.areIntersecting(a1, a2));
  }

  SECTION("timespeed test") {

    Telluric p1 = Telluric(Vector(0, 0, 0), Vector(0, 0, 0), nullptr, nullptr);

    Telluric p2 = Telluric(Vector(50, 0, 0), Vector(0, 0, 0), nullptr, nullptr);

    pm.setTimeSpeed(1);
    double normalSpeed =
        pm.calculateGravitationalAcceleration(p1, p2).magnitude() *
        pm.timeSpeed;

    pm.setTimeSpeed(2);
    double fastSpeed =
        pm.calculateGravitationalAcceleration(p1, p2).magnitude() *
        pm.timeSpeed;

    pm.setTimeSpeed(4);
    double veryFastSpeed =
        pm.calculateGravitationalAcceleration(p1, p2).magnitude() *
        pm.timeSpeed;

    pm.setTimeSpeed(8);
    double extremelyFastSpeed =
        pm.calculateGravitationalAcceleration(p1, p2).magnitude() *
        pm.timeSpeed;

    pm.setTimeSpeed(0);
    double zeroSpeed =
        pm.calculateGravitationalAcceleration(p1, p2).magnitude() *
        pm.timeSpeed;

    REQUIRE_THAT(fastSpeed, Catch::Matchers::WithinAbs(2 * normalSpeed, 0.001));
    REQUIRE_THAT(veryFastSpeed,
                 Catch::Matchers::WithinAbs(4 * normalSpeed, 0.001));
    REQUIRE_THAT(extremelyFastSpeed,
                 Catch::Matchers::WithinAbs(8 * normalSpeed, 0.001));
    REQUIRE_THAT(zeroSpeed, Catch::Matchers::WithinAbs(0, 0.001));
  }

  SECTION("graviational energy test") {
    Star s = Star(Vector(0, 0, 0), Vector(0, 0, 0), nullptr, nullptr);
    Telluric t =
        Telluric(Vector(1000, 0, 0), Vector(0, 0, 0), nullptr, nullptr);

    double energy = pm.calculateGravitationalEnergy(t, s);

    REQUIRE_THAT(energy, Catch::Matchers::WithinAbs(-1e9, 0.01));

    t.setPosition(Vector(2000, 0, 0));

    energy = pm.calculateGravitationalEnergy(t, s);

    REQUIRE_THAT(energy, Catch::Matchers::WithinAbs(-5e8, 0.01));

    Asteroid a = Asteroid(Vector(100, 0, 0), Vector(0, 0, 0), nullptr, nullptr);

    energy = pm.calculateGravitationalEnergy(a, s);

    REQUIRE_THAT(energy, Catch::Matchers::WithinAbs(-1e6, 0.01));
  }

  SECTION("remove planet testing") {
    std::weak_ptr<Planet> planetToDelete = pm.planets.front();

    std::shared_ptr<Planet> randomPlanet = std::make_shared<Planet>(
        Vector(0, 0, 0), Vector(0, 0, 0), nullptr, nullptr);

    std::weak_ptr<Planet> randomPlanetWk = randomPlanet;

    pm.removePlanet(randomPlanetWk);
    // no removal should happen

    REQUIRE(distance(pm.planets.begin(), pm.planets.end()) == 1);

    pm.removePlanet(planetToDelete);

    REQUIRE(distance(pm.planets.begin(), pm.planets.end()) == 0);
  }
}
