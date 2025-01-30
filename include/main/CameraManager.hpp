#pragma once

#include "ISceneNode.h"
#include <irrlicht.h>
#include <memory>

using namespace irr;

using namespace scene;

class CameraManager {
public:
  CameraManager(irr::scene::ISceneManager *smgr);
  void updatePosition();

  void resetDelta();
  void updateAngles(irr::core::vector2di const &newPos);

  void updateRadius(float wheelDelta);
  void reset();

  std::weak_ptr<ISceneNode> getPlanet();
  void setSelectedPlanet(std::weak_ptr<ISceneNode> planet);

private:
  std::weak_ptr<ISceneNode> selectedPlanet;
  ICameraSceneNode *camera;

  irr::core::vector2di previousPos;

  double radius;
  double theta;
  double phi;

  bool flag = false;
};
