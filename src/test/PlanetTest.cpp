#define private public
#define protected public
/*
 * Basically, this changes all privates and protecteds to publics in the other
 * classes, which means that I can access them to test the code
 */

#include "catch.h"
#include "main/planets/Asteroid.hpp"
#include "main/planets/Gas.hpp"
#include <cmath>

TEST_CASE("Planet Testing") {

  Asteroid a = Asteroid(Vector(0, 0, 0), Vector(0, 0, 0));
  Gas g = Gas(Vector(0, 0, 0), Vector(0, 0, 0));

  SECTION("rotation testing") {
    a.updateRotation();
    g.updateRotation();
    REQUIRE(a.rotation == 10);
    REQUIRE(g.rotation == 1);
  }

  SECTION("size and mass testing") {
    REQUIRE(a.getSize() == 1 * pow(10, 2));
    REQUIRE(a.getMass() == 2 * pow(10, 9));

    REQUIRE(g.getSize() == 7 * pow(10, 7));
    REQUIRE(g.getMass() == 2 * pow(10, 27));
  }
}
