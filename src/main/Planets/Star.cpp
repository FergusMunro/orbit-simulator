#include "main/planets/Star.hpp"
#include "main/Planet.hpp"
#include <cmath>

Star::Star(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 7 * pow(10, 8);
  mass = 2 * pow(10, 30);
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off sun
}

void Star::drawPlanet() {
  // TODO
}

// getters and setters
__float128 Star::getSize() { return size; }
