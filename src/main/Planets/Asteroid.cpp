#include "main/planets/Asteroid.hpp"
#include "main/Planet.hpp"
#include <cmath>

Asteroid::Asteroid(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 1 * pow(10, 2);
  mass = 2 * pow(10, 9);
  rotation_rate = 10;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // radius and mass of typical medium asteroid
}

void Asteroid::drawPlanet() {
  // TODO
}

// getters and setters
int Asteroid::getSize() { return size; }
