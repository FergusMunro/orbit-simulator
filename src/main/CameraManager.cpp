#include "main/CameraManager.hpp"
#include "ISceneNode.h"
#include "main/Macros.hpp"

#include <cmath>
#include <irrlicht.h>

CameraManager::CameraManager(irr::scene::ISceneManager *smgr) {

  camera = smgr->addCameraSceneNode();

  camera->setFarValue(1e6);
  camera->setPosition(core::vector3df(0, 0, 0));

  radius = 1000;
  theta = 0;
  phi = 0;
}

void CameraManager::updatePosition() {

  if (selectedPlanet.lock()) {

    core::vector3df position = selectedPlanet.lock()->getPosition();

    position.X = position.X + radius * sin(phi) * cos(theta);
    position.Y = position.Y + radius * cos(phi);
    position.Z = position.Z + radius * sin(phi) * sin(theta);

    camera->setPosition(position);
    camera->setTarget(selectedPlanet.lock()->getPosition());
  }
}

void CameraManager::setSelectedPlanet(std::weak_ptr<ISceneNode> planet) {
  selectedPlanet = planet;
}

void CameraManager::resetDelta() { flag = false; }

void CameraManager::updateAngles(irr::core::vector2di const &newPos) {

  if (flag) {
    irr::core::vector2di delta = newPos - previousPos;

    theta -= delta.X * 0.005;
    phi += delta.Y * 0.005;

    theta = fmod(theta, 2 * CONST_PI);
    phi = fmod(phi, 2 * CONST_PI);

  } else {
    flag = true;
  }

  previousPos = newPos;
}

void CameraManager::updateRadius(float wheelDelta) {
  radius -= 100 * wheelDelta;

  // we subtract because scrolling out should increase radius but scrolling out
  // is negative
}
