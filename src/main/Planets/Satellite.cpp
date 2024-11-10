#include "main/planets/Satellite.hpp"
#include "main/Planet.hpp"

Satellite::Satellite(const Vector &_position, const Vector &_velocity)
    : Planet(_position, _velocity) {

  size = 1;
  mass = 10;
  rotation_rate = 5;
  pathToTexture = "assets/planetTextures/asteroid.jpg";

  // based of very small satellite
}

void Satellite::drawPlanet() {
  // TODO
}

// getters and setters
int Satellite::getSize() { return size; }
