#include "main/Planet.hpp"
#include "main/planets/Asteroid.hpp"

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 1;
  mass = 10;
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based of very small satellite
}
