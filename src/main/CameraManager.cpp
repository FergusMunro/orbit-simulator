#include "main/CameraManager.hpp"
#include "ISceneNode.h"
#include "main/Macros.hpp"

#include <algorithm>
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
    phi -= delta.Y * 0.005;
    // subracting the deltas results in a camera that feels nicer to control

    theta = fmod(theta, 2 * CONST_PI);
    phi = std::clamp(phi, MIN_PHI, MAX_PHI);
    // cannot clamp at exact values as this causes camera to lose direction when
    // focusing on a planet

  } else {
    flag = true;
    // flag needed to ensure that only dragging results in moving of camera
  }

  previousPos = newPos;
}

void CameraManager::updateRadius(float wheelDelta) {
  radius -= 100 * wheelDelta;

  if (radius < 0) {
    radius = 0;
  }

  // we subtract because scrolling out should increase radius but scrolling out
  // is negative
}

void CameraManager::reset() {

  camera->setPosition(core::vector3df(0, 0, 0));

  radius = 1000;
  theta = 0;
  phi = 0;
}
