#include "main/planets/Asteroid.hpp"
#include "main/Planet.hpp"
#include <cmath>

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 4 * pow(10, 3);
  mass = 1 * pow(10, 3);
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // radius and mass of typical medium asteroid
}
