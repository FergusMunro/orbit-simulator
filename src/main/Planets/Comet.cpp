#include "main/planets/Comet.hpp"
#include "main/Planet.hpp"
#include <cmath>

Comet::Comet(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 4 * pow(10, 3);
  mass = 3 * pow(10, 14);
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // radius and mass based off of halley's comet
}

void Comet::drawPlanet() {
  // TODO
}

// getters and setters
__float128 Comet::getSize() { return size; }
