#include "main/Vector.hpp"
#include "catch.h"

TEST_CASE("testing vector") {
  Vector v1 = Vector(6, 7, 3);
  Vector v2 = Vector(8, 7, 1);

  Vector v3 = Vector(0, 0, 0);

  SECTION("vector addition") {
    v3 = v1 + v2;

    REQUIRE_THAT(v3.x, Catch::Matchers::WithinAbs(14, 0.001));
    REQUIRE_THAT(v3.y, Catch::Matchers::WithinAbs(14, 0.001));
    REQUIRE_THAT(v3.z, Catch::Matchers::WithinAbs(4, 0.001));
  }

  SECTION("vector subtraction") {

    v3 = v1 - v2;

    REQUIRE_THAT(v3.x, Catch::Matchers::WithinAbs(-2, 0.001));
    REQUIRE_THAT(v3.y, Catch::Matchers::WithinAbs(0, 0.001));
    REQUIRE_THAT(v3.z, Catch::Matchers::WithinAbs(2, 0.001));
  }

  SECTION("scalar multiplication") {
    v3 = v1 * 5;

    REQUIRE_THAT(v3.x, Catch::Matchers::WithinAbs(30, 0.001));
    REQUIRE_THAT(v3.y, Catch::Matchers::WithinAbs(35, 0.001));
    REQUIRE_THAT(v3.z, Catch::Matchers::WithinAbs(15, 0.001));
  }

  SECTION("scalar division") {
    double num = 1.0 / 4;

    v3 = v1 * num;

    REQUIRE_THAT(v3.x, Catch::Matchers::WithinAbs(1.5, 0.001));
    REQUIRE_THAT(v3.y, Catch::Matchers::WithinAbs(1.75, 0.001));
    REQUIRE_THAT(v3.z, Catch::Matchers::WithinAbs(0.75, 0.001));
  }

  SECTION("magntude") {

    REQUIRE_THAT(v1.magnitude(), Catch::Matchers::WithinAbs(9.695, 0.001));
    REQUIRE_THAT(v2.magnitude(), Catch::Matchers::WithinAbs(10.677, 0.001));
  }

  SECTION("normalise") {
    v3 = v1.normalise();

    REQUIRE_THAT(v3.magnitude(), Catch::Matchers::WithinAbs(1.0, 0.001));

    REQUIRE_THAT(v3.x, Catch::Matchers::WithinAbs(0.619, 0.001));
    REQUIRE_THAT(v3.y, Catch::Matchers::WithinAbs(0.722, 0.001));
    REQUIRE_THAT(v3.z, Catch::Matchers::WithinAbs(0.309, 0.001));
  }

  SECTION("dot and cross product") {
    double dot = Vector::dot(v1, v2);
    v3 = Vector::cross(v1, v2);

    REQUIRE_THAT(dot, Catch::Matchers::WithinAbs(100, 0.001));

    REQUIRE_THAT(v3.x, Catch::Matchers::WithinAbs(-14, 0.001));
    REQUIRE_THAT(v3.y, Catch::Matchers::WithinAbs(18, 0.001));
    REQUIRE_THAT(v3.z, Catch::Matchers::WithinAbs(-14, 0.001));
  }
}
