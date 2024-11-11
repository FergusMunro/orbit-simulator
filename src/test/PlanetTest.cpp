#define private public
#define protected public
/*
 * Basically, this changes all privates and protecteds to publics in the other
 * classes, which means that I can access them to test the code
 */

#include "catch.h"
#include "main/planets/Asteroid.hpp"
#include "main/planets/Gas.hpp"

TEST_CASE("Planet Testing") {

  Asteroid a = Asteroid(Vector(0, 0, 0), Vector(0, 0, 0));
  Gas g = Gas(Vector(0, 0, 0), Vector(0, 0, 0));

  SECTION("rotation testing") {
    a.updateRotation();
    g.updateRotation();
    REQUIRE(a.rotation == 10);
    REQUIRE(g.rotation == 1);
  }
}
