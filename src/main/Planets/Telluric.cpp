#include "main/planets/Telluric.hpp"
#include "main/Planet.hpp"
#include <cmath>

Telluric::Telluric(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 6 * pow(10, 6);
  mass = 6 * pow(10, 24);
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based off of earth
}

void Telluric::drawPlanet() {
  // TODO
}

// getters and setters
int Telluric::getSize() { return size; }
