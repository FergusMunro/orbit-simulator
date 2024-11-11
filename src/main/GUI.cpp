#include "main/GUI.hpp"
#include "main/planets/Telluric.hpp"

GUI::GUI() {
  pm.addPlanet(Telluric(Vector(0, 0, 0), Vector(0, 0, 0)));
  // basic driver code to set up a basic simulation
}

void GUI::run() {
  // runs constructor

  GUI gui = GUI();

  // forever loop that updates positions of planets and then draws planets

  while (1) {
    gui.pm.updatePositions();
    gui.pm.drawPlanets();
  }
}
