#define private public
#define protected public
/*
 * Basically, this changes all privates and protecteds to publics in the other
 * classes, which means that I can access them to test the code
 */

#include "catch.h"
#include "main/planets/Asteroid.hpp"
#include "main/planets/Gas.hpp"
#include "main/planets/Telluric.hpp"

#include <cmath>
#include <irrlicht.h>

TEST_CASE("Planet Testing") {

  Telluric t = Telluric(Vector(0, 0, 0), Vector(0, 0, 0), nullptr, nullptr);
  Gas g = Gas(Vector(0, 0, 0), Vector(0, 0, 0), nullptr, nullptr);

  SECTION("rotation testing") {
    t.updateRotation();
    g.updateRotation();
    REQUIRE(t.rotation == 5);
    REQUIRE(g.rotation == 1);
  }

  SECTION("size and mass testing") {
    REQUIRE(t.getSize() == 30);
    REQUIRE(t.getMass() == 100);

    REQUIRE(g.getSize() == 120);
    REQUIRE(g.getMass() == 1000);
  }

  SECTION("kinetic energy testing") {
    t.setVelocity(Vector(0, 100, 0));

    REQUIRE_THAT(t.getKineticEnergy(),
                 Catch::Matchers::WithinAbs(500000, 0.01));

    t.setMass(50);

    REQUIRE_THAT(t.getKineticEnergy(),
                 Catch::Matchers::WithinAbs(250000, 0.01));

    t.setVelocity(Vector(0, 200, 0));

    REQUIRE_THAT(t.getKineticEnergy(), Catch::Matchers::WithinAbs(1e6, 0.01));

    Asteroid a =
        Asteroid(Vector(0, 0, 0), Vector(0, 0, 1000), nullptr, nullptr);

    REQUIRE_THAT(a.getKineticEnergy(), Catch::Matchers::WithinAbs(5000, 0.01));
  }
}
