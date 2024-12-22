#include "main/CameraManager.hpp"
#include "ISceneNode.h"

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

    phi += 0.01;
    theta -= 0.01;

    core::vector3df position = selectedPlanet.lock()->getPosition();

    position.X = position.X + radius * cos(phi) * sin(theta);
    position.Y = position.Y + radius * cos(phi) * cos(theta);
    position.Z = position.Z + radius * sin(phi);

    camera->setPosition(position);
    camera->setTarget(selectedPlanet.lock()->getPosition());
  }
}

void CameraManager::setSelectedPlanet(std::weak_ptr<ISceneNode> planet) {
  selectedPlanet = planet;
}
