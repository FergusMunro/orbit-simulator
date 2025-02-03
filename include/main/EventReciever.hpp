#pragma once

#include <irrlicht.h>

using namespace irr;

class EventReceiver : public IEventReceiver {
public:
  struct SMouseState {
    core::position2di Position;
    bool leftButtonDown;
    bool rightButtonDown;
    bool shouldSelectPlanet;
    float wheel;
    SMouseState()
        : leftButtonDown(false), shouldSelectPlanet(false),
          rightButtonDown(false) {}
  } MouseState;

  bool wheelReset;
  void update();
  virtual int IsKeyDown(EKEY_CODE keyCode) const;

  virtual bool OnEvent(const SEvent &event);

  // This is the one method that we have to implement
  const SMouseState &GetMouseState(void) const { return MouseState; }

  EventReceiver();

  bool getPlanetWindowState() { return createPlanetWindowIsOpen; }

  void setPlanetWindowSate(bool _planetWindowStatus) {
    createPlanetWindowIsOpen = _planetWindowStatus;
  }

  bool getPlanetMenuState() { return planetMenuIsOpen; }
  void setPlanetMenuState(bool _planetMenuStatus) {
    planetMenuIsOpen = _planetMenuStatus;
  }

private:
  int KeyIsDown[KEY_KEY_CODES_COUNT];
  bool createPlanetWindowIsOpen = false;
  bool planetMenuIsOpen = false;
};
