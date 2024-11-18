#define private public
#define protected public
/*
 * Basically, this changes all privates and protecteds to publics in the other
 * classes, which means that I can access them to test the code
 */

#include "catch.h"

#include "main/PlanetManager.hpp"
#include "main/Vector.hpp"
#include "main/planets/Satellite.hpp"
#include <cmath>
#include <memory>

TEST_CASE("planet Manager Tests") {
  PlanetManager pm;
  Satellite s = Satellite(Vector(0, 0, 0), Vector(0, 0, 0));

  pm.addPlanet(std::make_unique<Satellite>(s));

  SECTION("linked list test") {

    auto it = pm.planets.begin();

    REQUIRE((**it).getMass() == s.getMass());
  }
}
