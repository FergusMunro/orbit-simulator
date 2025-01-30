#define private public
#define protected public
/*
 * Basically, this changes all privates and protecteds to publics in the other
 * classes, which means that I can access them to test the code
 */

#include "main/Orbit.hpp"
#include "catch.h"
#include "main/planets/Star.hpp"

#include <memory>

TEST_CASE("orbit test") {

  Orbit o = Orbit(0, 0, 0, 0, 0, 0);

  SECTION("toggle testing") {
    REQUIRE(!o.keplersFirst);
    o.toggleKeplersFirst();
    REQUIRE(o.keplersFirst);

    REQUIRE(o.keplersSecond % 2 != 0);
    REQUIRE(o.keplersSecond % 3 != 0);
    o.toggleKeplersSecond();
    REQUIRE(o.keplersSecond % 2 == 0);
    o.toggleConstantSweeping();
    REQUIRE(o.keplersSecond % 3 == 0);

    o.toggleKeplersSecond();
    o.toggleConstantSweeping();

    REQUIRE(o.keplersSecond % 2 != 0);
    REQUIRE(o.keplersSecond % 3 != 0);
  }

  SECTION("convert back and forth from velocity testing") {
    std::shared_ptr<Planet> p = std::make_shared<Star>(
        Vector(1000, 5151, 515), Vector(5, 55, 765), nullptr, nullptr);

    Vector pos = Vector(14, 456, 3000);
    Vector vel = Vector(1825, 500, -80);

    o.stateVectorsToOrbitalElements(pos, vel, p);
    pos_and_vel posvel = o.orbitalElementsToStateVectors(p);

    double tolerance = 1e-3;

    // Check position components

    REQUIRE_THAT(pos.x,
                 Catch::Matchers::WithinAbs(posvel.position.x, tolerance));
    REQUIRE_THAT(pos.y,
                 Catch::Matchers::WithinAbs(posvel.position.y, tolerance));
    REQUIRE_THAT(pos.z,
                 Catch::Matchers::WithinAbs(posvel.position.z, tolerance));

    // Check velocity components

    REQUIRE_THAT(vel.x,
                 Catch::Matchers::WithinAbs(posvel.velocity.x, tolerance));
    REQUIRE_THAT(vel.y,
                 Catch::Matchers::WithinAbs(posvel.velocity.y, tolerance));
    REQUIRE_THAT(vel.z,
                 Catch::Matchers::WithinAbs(posvel.velocity.z, tolerance));
  }

  SECTION("state vectors -> orbital elements test") {
    std::shared_ptr<Planet> p = std::make_shared<Star>(
        Vector(0, 0, 0), Vector(0, 0, 0), nullptr, nullptr);
    p->setMass(39.86);

    o.stateVectorsToOrbitalElements(Vector(1000, 5000, 7000), Vector(3, 4, 5),
                                    p);

    REQUIRE_THAT(o.angularMomentum,
                 Catch::Matchers::WithinAbs(19646.883, 0.001));
    REQUIRE_THAT(o.inclination, Catch::Matchers::WithinAbs(2.1651, 0.001));
    REQUIRE_THAT(o.rightAscension, Catch::Matchers::WithinAbs(3.326, 0.001));
    REQUIRE_THAT(o.eccentricity, Catch::Matchers::WithinAbs(0.948, 0.001));
    REQUIRE_THAT(o.argp, Catch::Matchers::WithinAbs(5.289, 0.001));
    REQUIRE_THAT(o.trueanomaly, Catch::Matchers::WithinAbs(2.786, 0.001));
  }

  SECTION("orbital elements -> state vectors test") {
    Orbit o =
        Orbit(19646.883, 2.16508094, 3.32694662, 0.948, 5.28991843, 2.78572002);
    std::shared_ptr<Planet> p = std::make_shared<Star>(
        Vector(0, 0, 0), Vector(0, 0, 0), nullptr, nullptr);
    p->setMass(39.86);

    pos_and_vel posvel = o.orbitalElementsToStateVectors(p);

    REQUIRE_THAT(1000, Catch::Matchers::WithinAbs(posvel.position.x, 5));
    REQUIRE_THAT(5000, Catch::Matchers::WithinAbs(posvel.position.y, 20));
    REQUIRE_THAT(7000, Catch::Matchers::WithinAbs(posvel.position.z, 30));

    // Check velocity components

    REQUIRE_THAT(3, Catch::Matchers::WithinAbs(posvel.velocity.x, 0.01));
    REQUIRE_THAT(4, Catch::Matchers::WithinAbs(posvel.velocity.y, 0.01));
    REQUIRE_THAT(5, Catch::Matchers::WithinAbs(posvel.velocity.z, 0.01));
  }
}
