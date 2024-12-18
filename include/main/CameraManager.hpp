#pragma once

#include "ISceneNode.h"
#include <irrlicht.h>
#include <memory>

using namespace irr;

using namespace scene;

class CameraManager {
public:
  CameraManager(irr::scene::ISceneManager *smgr);
  void setSelectedPlanet(std::weak_ptr<ISceneNode> planet);
  void updatePosition();

private:
  std::weak_ptr<ISceneNode> selectedPlanet;
  ICameraSceneNode *camera;

  double radius;
  double theta;
  double phi;
};
