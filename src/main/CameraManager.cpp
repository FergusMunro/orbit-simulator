#include "main/CameraManager.hpp"
#include "ISceneNode.h"
#include "main/Macros.hpp"
#include "vector3d.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <irrlicht.h>

CameraManager::CameraManager(irr::scene::ISceneManager *smgr) {

  // set up starting state of camera

  camera = smgr->addCameraSceneNode();

  camera->setFarValue(1e6); // so we can see distant planets
  camera->setPosition(core::vector3df(0, 0, 0));

  // initialize starting variables
  radius = 1000;
  theta = 1.5;
  phi = 1.5;
}

void CameraManager::updatePosition() {

  if (selectedPlanet.lock()) {

    core::vector3df position = selectedPlanet.lock()->getPosition();

    // use parametric formula to get position of camera from angles/radius
    position.X = position.X + radius * sin(phi) * cos(theta);
    position.Y = position.Y + radius * cos(phi);
    position.Z = position.Z + radius * sin(phi) * sin(theta);

    camera->setPosition(position);

    camera->setTarget(selectedPlanet.lock()->getPosition());
    // look at the selected planet
  } else {
    std::cerr << "not locked on to any planet\n";
  }
}

void CameraManager::resetDelta() {
  flag = false;
  // this is used to check if the mouse has been held down the previous frame.
  // if it hasn't, the flag variable is set to false which means we don't update
  // the angles
}

void CameraManager::updateAngles(irr::core::vector2di const &newPos) {

  if (flag) {
    // only run if the mouse was held down the previous frame
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
    radius = 0; // stop radius going through planet
  }

  // we subtract because scrolling out should increase radius but scrolling out
  // is negative
}

void CameraManager::reset() {
  // same as constructor, but we don't initialize the camera this time

  camera->setPosition(core::vector3df(0, 0, 0));
  camera->setTarget(
      core::vector3df(0, 0, 1)); // to be facing forwards, which we are doing by
                                 // default when initialising the camera

  radius = 1000;
  theta = 1.5;
  phi = 1.5;
}

void CameraManager::setSelectedPlanet(std::weak_ptr<ISceneNode> planet) {
  selectedPlanet = planet;
}

std::weak_ptr<ISceneNode> CameraManager::getPlanet() { return selectedPlanet; }
