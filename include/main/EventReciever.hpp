#pragma once

#include <irrlicht.h>

using namespace irr;

class EventReceiver : public IEventReceiver {
public:
  struct SMouseState {
    core::position2di Position;
    bool LeftButtonDown;
    SMouseState() : LeftButtonDown(false) {}
  } MouseState;

  virtual bool OnEvent(const SEvent &event);

  // This is the one method that we have to implement
  const SMouseState &GetMouseState(void) const { return MouseState; }

  EventReceiver() {}
};
