#include "shooting-simulator.h"

namespace basketballgame {

ShootingSimulator::ShootingSimulator() {
  ci::app::setWindowSize(shooter_.kWindowWidth, shooter_.kWindowHeight);
  was_space_pressed_ = false;
  is_shooting_two_ = false;
  power_already_changed_ = false;
  //Initially set angle_of_elevation to 4
  angle_of_elevation_ = 4;
}

void ShootingSimulator::draw() {
  ci::Color background_color("white");
  ci::gl::clear(background_color);

  shooter_.Display();
}

void ShootingSimulator::update() {
  shooter_.EndGame();

  //Checks if the ball touches the ground or the right edge of the window and moves the ball back to its original position
  if (shooter_.GetBasketball().GetPosition().y >= shooter_.kWindowHeight ||
  shooter_.GetBasketball().GetPosition().x >= shooter_.kWindowWidth) {
    if (is_shooting_two_) {
      shooter_.ChangeBasketballPosition(2);
      shooter_.SetPower(600);
    } else {
      shooter_.ChangeBasketballPosition(3);
      shooter_.SetPower(600);
    }

    was_space_pressed_ = false;
    power_already_changed_ = false;
    shooter_.SetState(GameState::kBeforeSpacePressed);
    shooter_.SetScoreIncreasingBoolean(false);
  }

  //Nested if statements checking if the user has held down and released the space bar
  if (was_space_pressed_) {
    if (shooter_.GetState() == GameState::kBallReleased) {
      if (!power_already_changed_) {
        shooter_.ChangeBallVelocityFromPower();
        shooter_.ChangeAngle(angle_of_elevation_);
      }

      power_already_changed_ = true;
      shooter_.AdvanceOneFrame();
    }
  }
}

void ShootingSimulator::keyDown(KeyEvent event) {
  //If the space bar is pressed, change the state of the game to kPowerAccumulating
  if (event.getCode() == KeyEvent::KEY_SPACE) {
    was_space_pressed_ = true;
    shooter_.SetState(GameState::kPowerAccumulating);
  }

  //Moves ball to two and three point line accordingly
  if (shooter_.GetState() == GameState::kBeforeSpacePressed) {
    if (event.getCode() == KeyEvent::KEY_f) {
      is_shooting_two_ = true;
      shooter_.ChangeBasketballPosition(2);
    } else if (event.getCode() == KeyEvent::KEY_b) {
      is_shooting_two_ = false;
      shooter_.ChangeBasketballPosition(3);
    }
  }

  //Allows the user to change angle based on the number keys on the keyboard
  if (shooter_.GetState() == GameState::kBeforeSpacePressed) {
    if ((event.getChar() - '0') >= 0 && (event.getChar() - '0') <= 9) {
      angle_of_elevation_ = event.getChar() - '0';
    }
  }

  //Accumulates power while the spacebar is held down
  if (shooter_.GetState() == GameState::kPowerAccumulating) {
    if (event.getCode() == KeyEvent::KEY_SPACE) {
      shooter_.AccumulatePower();
    }
  }

  //Allows user to start the game
  if (shooter_.GetState() == GameState::kGameNotStarted) {
    if (event.getCode() == KeyEvent::KEY_s) {
      shooter_.StartTime();
    }
  }

  //Allows user to restart the game once they have finished a round
  if (shooter_.GetState() == GameState::kGameHasFinished) {
    if (event.getCode() == KeyEvent::KEY_r) {
      shooter_.Reset();
      shooter_.StartTime();
      was_space_pressed_ = false;
      is_shooting_two_ = false;
      power_already_changed_ = false;
      angle_of_elevation_ = 4;
    }
  }
}

void ShootingSimulator::keyUp(KeyEvent event) {
  //If the space bar is released after it was held down for a period of time, the ball is released
  if (shooter_.GetState() == GameState::kPowerAccumulating) {
    if (event.getCode() == KeyEvent::KEY_SPACE) {
      shooter_.SetState(GameState::kBallReleased);
    }
  }
}
}
