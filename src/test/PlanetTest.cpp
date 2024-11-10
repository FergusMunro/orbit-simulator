#include "main/planets/Gas.hpp"
#define private public
/*
 * Basically, this changes all privates to publics in the other classes, which
 * means that I can access them to test the code
 */

#include "catch.h"
#include "main/planets/Asteroid.hpp"

TEST_CASE("Planet Testing") {

  Asteroid a = Asteroid(Vector(0, 0, 0), Vector(0, 0, 0));
  Gas g = Gas(Vector(0, 0, 0), Vector(0, 0, 0));

  SECTION("rotation testing") {}
}
