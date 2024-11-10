#include "main/planets/Asteroid.hpp"
#include "main/Planet.hpp"
#include <cmath>

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 4 * pow(10, 3);
  mass = 1 * pow(10, 3);
  rotation_rate = 10;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // radius and mass of typical medium asteroid
}

void Asteroid::drawPlanet() {
  // TODO
}

// getters and setters
int Asteroid::getSize() { return size; }
