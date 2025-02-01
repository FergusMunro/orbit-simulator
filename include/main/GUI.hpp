#pragma once

#include "IGUIButton.h"
#include "IGUIComboBox.h"
#include "IGUIEditBox.h"
#include "IGUIStaticText.h"
#include "main/CameraManager.hpp"
#include "main/EventReciever.hpp"
#include "main/PlanetManager.hpp"

#include <irrlicht.h>
#include <map>
#include <memory>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GUI {
public:
  static void run();

  /* This class uses a private constructor and a static method that instead
   * creates the class, which means there can only be one GUI which makes the
   * code much simpler and less easy to missuse.
   */

private:
  GUI();
  void addPlanet(const Vector &_position, const Vector &_velocity, int type);

  // decomposed procedues
  void createTopBar();
  void addStartingPlanets();
  void handleMouseInput();
  void handleButtonPresses();
  void createAddPlanetPopUp();
  bool createPlanetFromInput();
  void openTitleScreen();

  // important variables and attributes
  PlanetManager pm;
  std::unique_ptr<CameraManager> camera;

  std::map<irr::scene::ISceneNode *, std::weak_ptr<irr::scene::ISceneNode>>
      scenePointerMap;
  // reciever, mousepos,
  std::unique_ptr<EventReceiver> receiver;
  vector2di mousepos;
  bool openPopUpFlag = true;
  bool titleScreenOpen = true;

  // irrlicht pointers

  IrrlichtDevice *device;

  IVideoDriver *driver;
  ISceneManager *smgr;
  IGUIEnvironment *guienv;
  ISceneCollisionManager *colmgr;

  // gui elements for top bar

  IGUIStaticText *topBar;

  IGUIButton *resetButton;
  IGUIButton *addPlanetButton;

  IGUIButton *pauseButton;
  IGUIButton *normalSpeedButton;
  IGUIButton *fastSpeedButton;
  IGUIButton *veryFastButton;
  IGUIButton *extremelyFastButton;

  // gui elements for add planet window

  IGUIWindow *addPlanetWindow;
  IGUIComboBox *planetSelect;
  IGUIComboBox *inputTypeSelect;
  IGUIButton *createPlanetButton;

  IGUIEditBox *xPosEditBox;
  IGUIEditBox *yPosEditBox;
  IGUIEditBox *zPosEditBox;
  IGUIEditBox *xVelEditBox;
  IGUIEditBox *yVelEditBox;
  IGUIEditBox *zVelEditBox;

  IGUIEditBox *radiusEditBox;
  IGUIEditBox *eccentriciyEditBox;
  IGUIEditBox *inclinationEditBox;
  IGUIEditBox *argpEditBox;
  IGUIEditBox *rightAscensionEditBox;
  IGUIEditBox *trueAnomalyEditBox;

  IGUIStaticText *warningText;

  // gui elements for title title screen

  IGUIButton *startSimulationButton;
  IGUIButton *helpButton;
};
