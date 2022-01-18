#pragma once

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include "basketball.h"
#include "shooter.h"
#include <cmath>

using cinder::app::KeyEvent;
using cinder::app::MouseEvent;

namespace basketballgame {

class ShootingSimulator : public ci::app::App {
 public:

  /**
   * Default constructor for the shooting simulator.
   */
  ShootingSimulator();

  /**
   * Overrides the draw method from cinder.
   */
  void draw() override;

  /**
   * Overrides the update method from cinder.
   */
  void update() override;

  /**
   * Overrides the keyDown method from cinder.
   * @param event The KeyEvent object.
   */
  void keyDown(KeyEvent event) override;

  /**
   * Overrides the keyUp method from cinder.
   * @param event The KeyEvent object.
   */
  void keyUp(KeyEvent event) override;

 private:
  bool was_space_pressed_; //Boolean representing whether the space bar was pressed
  bool is_shooting_two_;  //Boolean representing whether the user was shooting a two pointer or not
  //Boolean representing whether the power has already been changed so that it stays the same after the ball's release
  bool power_already_changed_;
  size_t angle_of_elevation_;
  Shooter shooter_;
};
}
