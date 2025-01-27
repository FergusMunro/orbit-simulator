#define private public
#define protected public
/*
 * Basically, this changes all privates and protecteds to publics in the other
 * classes, which means that I can access them to test the code
 */

#include "main/Orbit.hpp"
#include "catch.h"

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

  SECTION("convert back and forth from velocity testing") {}
}
