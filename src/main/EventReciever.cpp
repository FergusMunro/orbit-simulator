#include "main/EventReciever.hpp"
#include "IEventReceiver.h"

bool EventReceiver::OnEvent(const SEvent &event) {
  if (event.EventType == EET_MOUSE_INPUT_EVENT) {
    switch (event.MouseInput.Event) {
    case EMIE_LMOUSE_PRESSED_DOWN:
      MouseState.leftButtonDown = true;
      break;

    case EMIE_LMOUSE_LEFT_UP:
      MouseState.leftButtonDown = false;
      break;

    case EMIE_MMOUSE_PRESSED_DOWN:
      MouseState.middleButtonDown = true;
      break;

    case EMIE_MMOUSE_LEFT_UP:
      MouseState.middleButtonDown = false;
      break;

    case EMIE_MOUSE_MOVED:
      MouseState.Position.X = event.MouseInput.X;
      MouseState.Position.Y = event.MouseInput.Y;
      break;

    case EMIE_MOUSE_WHEEL:
      MouseState.wheel = event.MouseInput.Wheel;
      wheelReset = true;

    default:
      break;
    }
  }

  return false;
}

void EventReceiver::update() {
  if (wheelReset) {
    MouseState.wheel = 0;
    wheelReset = false;
  }
}
