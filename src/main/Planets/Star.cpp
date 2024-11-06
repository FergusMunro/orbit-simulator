#include "main/Planet.hpp"
#include "main/planets/Asteroid.hpp"
#include <cmath>

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 7 * pow(10, 8);
  mass = 2 * pow(10, 30);
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off sun
}
