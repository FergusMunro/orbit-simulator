#pragma once

#include "main/Orbit.hpp"
#include "main/Vector.hpp"
#include <memory>

#include <irrlicht.h>

class Planet {

public:
  // methods

  virtual void drawPlanet() = 0;
  void updateRotation();

  // Getters and Setters

  __float128 getMass() const;
  void setMass(__float128 _mass);
  Vector getPosition() const;
  void setPosition(const Vector &_position);
  Vector getVelocity() const;
  void setVelocity(const Vector &_velocity);
  __float128 getSize() const;

  std::weak_ptr<irr::scene::ISceneNode> getSceneNodePtr();

  void setOrbitedPlanet(Planet *planet);
  Planet *getOrbitedPlanet() const;

  // constructor
  Planet(const Vector &position, const Vector &velocity,
         irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);
  // destructor
  virtual ~Planet();

protected:
  // attributes

  __float128 mass;
  Orbit orbit;
  Vector position;
  Vector velocity;
  int rotation;
  int rotation_rate;
  irr::io::path pathToTexture;

  std::shared_ptr<irr::scene::ISceneNode> obj;

  __float128 size;

  Planet *pOrbitedPlanet;
};
