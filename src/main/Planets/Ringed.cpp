#include "main/Planet.hpp"
#include "main/planets/Asteroid.hpp"
#include <cmath>

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 6 * pow(10, 7);
  mass = 6 * pow(10, 26);
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off of saturn
}
