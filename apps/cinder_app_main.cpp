#include "shooting-simulator.h"

using basketballgame::ShootingSimulator;

void prepareSettings(ShootingSimulator::Settings* settings) {
  settings->setResizable(false);
  settings->setFrameRate(20.0f);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(ShootingSimulator, ci::app::RendererGl, prepareSettings);
