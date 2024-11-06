#include "main/Planet.hpp"
#include "main/planets/Asteroid.hpp"
#include <cmath>

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 4 * pow(10, 3);
  mass = 3 * pow(10, 14);
  rotation_rate = 1;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // radius and mass based off of halley's comet
}
