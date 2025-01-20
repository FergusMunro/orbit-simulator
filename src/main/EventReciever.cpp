#include "main/EventReciever.hpp"
#include "IEventReceiver.h"
#include "Keycodes.h"

bool EventReceiver::OnEvent(const SEvent &event) {

  if (event.EventType == irr::EET_KEY_INPUT_EVENT) {

    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  }

  if (event.EventType == EET_MOUSE_INPUT_EVENT) {
    switch (event.MouseInput.Event) {

    case EMIE_LMOUSE_PRESSED_DOWN:
      MouseState.leftButtonDown = true;

      if (IsKeyDown(irr::KEY_LCONTROL)) {

        MouseState.shouldSelectPlanet = true;
      }

      break;

    case EMIE_LMOUSE_LEFT_UP:
      MouseState.leftButtonDown = false;
      MouseState.shouldSelectPlanet = false;
      break;

    case EMIE_MOUSE_MOVED:
      MouseState.Position.X = event.MouseInput.X;
      MouseState.Position.Y = event.MouseInput.Y;
      break;

    case EMIE_MOUSE_WHEEL:
      MouseState.wheel = event.MouseInput.Wheel;

    default:
      break;
    }
  }

  return false;
}

void EventReceiver::update() {
  MouseState.wheel = 0;

  MouseState.shouldSelectPlanet = false;
}

int EventReceiver::IsKeyDown(EKEY_CODE keyCode) const {
  return KeyIsDown[keyCode];
}

EventReceiver::EventReceiver() {

  for (int i = 0; i < (sizeof(KeyIsDown) / sizeof(int)); i++) {

    KeyIsDown[i] = 0;
  }
}
