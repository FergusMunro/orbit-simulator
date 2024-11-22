#define private public
#define protected public
/*
 * Basically, this changes all privates and protecteds to publics in the other
 * classes, which means that I can access them to test the code
 */

#include "catch.h"

#include "main/PlanetManager.hpp"
#include "main/Vector.hpp"
#include "main/planets/Asteroid.hpp"
#include <cmath>
#include <memory>

TEST_CASE("planet Manager Tests") {
  PlanetManager pm;
  Asteroid s = Asteroid(Vector(0, 0, 0), Vector(0, 0, 0), nullptr);

  pm.addPlanet(Vector(0, 0, 0), Vector(0, 0, 0), nullptr);

  SECTION("linked list test") {

    auto it = pm.planets.begin();

    REQUIRE((**it).getMass() == s.getMass());
  }
}
