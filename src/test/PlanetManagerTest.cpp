#include "main/Macros.hpp"
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

  pm.addPlanet(Vector(0, 0, 0), Vector(0, 0, 0), nullptr, _Telluric);

  SECTION("linked list test") {

    auto it = pm.planets.begin();

    REQUIRE((**it).getMass() == 100);
  }

  SECTION("gravity test") {

    // TODO: fix this for new sets of values

    /*

    Telluric a1 = Telluric(Vector(4, 4, 4), Vector(0, 0, 0), nullptr);

    Telluric a2 = Telluric(Vector(6, 11, 30), Vector(0, 0, 0), nullptr);

    Vector acceleration = pm.calculateGravitationalAcceleration(a1, a2);

    REQUIRE_THAT(acceleration.magnitude(),
                 Catch::Matchers::WithinAbs(0.00018299, 0.00000001));

    REQUIRE_THAT(acceleration.x,
                 Catch::Matchers::WithinAbs(1.35548e-5, 0.00000001));
    REQUIRE_THAT(acceleration.y,
                 Catch::Matchers::WithinAbs(4.7442e-5, 0.00000001));
    REQUIRE_THAT(acceleration.z,
                 Catch::Matchers::WithinAbs(1.76213e-4, 0.00000001));

    a2.setMass(1e30);

    a1.setPosition(Vector(0, 0, 0));
    a2.setPosition(Vector(3000000, 16000000, 24000000));

    acceleration = pm.calculateGravitationalAcceleration(a1, a2);

    REQUIRE_THAT(acceleration.magnitude(),
                 Catch::Matchers::WithinAbs(79310.34483, 0.00001));

    REQUIRE_THAT(acceleration.x,
                 Catch::Matchers::WithinAbs(8204.51843, 0.0001));
    REQUIRE_THAT(acceleration.y,
                 Catch::Matchers::WithinAbs(43757.43163, 0.0001));
    REQUIRE_THAT(acceleration.z,
                 Catch::Matchers::WithinAbs(65636.14744, 0.0001));
    */
  }

  SECTION("intersection test") {

    Telluric a1 = Telluric(Vector(0, 0, 0), Vector(0, 0, 0), nullptr);

    // Intersecting Position

    Telluric a2 = Telluric(Vector(50, 0, 0), Vector(0, 0, 0), nullptr);

    REQUIRE(pm.areIntersecting(a1, a2));

    // Not intersecting position

    a2.setPosition(Vector(210, 0, 0));

    REQUIRE(!pm.areIntersecting(a1, a2));

    // Boundary - just touching - should count as intersection

    a2.setPosition(Vector(0, 0, 60));

    REQUIRE(pm.areIntersecting(a1, a2));
  }
}
