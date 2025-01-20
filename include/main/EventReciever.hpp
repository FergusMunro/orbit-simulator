#pragma once

#include <irrlicht.h>

using namespace irr;

class EventReceiver : public IEventReceiver {
public:
  struct SMouseState {
    core::position2di Position;
    bool leftButtonDown;
    bool shouldSelectPlanet;
    float wheel;
    SMouseState() : leftButtonDown(false), shouldSelectPlanet(false) {}
  } MouseState;

  bool wheelReset;
  void update();
  virtual int IsKeyDown(EKEY_CODE keyCode) const;

  virtual bool OnEvent(const SEvent &event);

  // This is the one method that we have to implement
  const SMouseState &GetMouseState(void) const { return MouseState; }

  EventReceiver();

private:
  int KeyIsDown[KEY_KEY_CODES_COUNT];
};
