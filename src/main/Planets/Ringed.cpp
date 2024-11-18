#include "main/planets/Ringed.hpp"
#include "main/Planet.hpp"
#include <cmath>

Ringed::Ringed(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 6 * pow(10, 7);
  mass = 6 * pow(10, 26);
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off of saturn
}

void Ringed::drawPlanet() {
  // TODO
}

// getters and setters
__float128 Ringed::getSize() { return size; }
