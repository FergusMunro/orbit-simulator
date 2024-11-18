#include "main/planets/Gas.hpp"
#include "main/Planet.hpp"
#include <cmath>

Gas::Gas(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 7 * pow(10, 7);
  mass = 2 * pow(10, 27);
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off of jupiter
}

void Gas::drawPlanet() {
  // TODO
}

// getters and setters
__float128 Gas::getSize() { return size; }
