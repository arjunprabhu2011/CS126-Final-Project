#pragma once
#include <cmath>
#include "basketball.h"

namespace basketballgame {
/**
 * An enumeration which represents the different states that the game can be in at a given time.
 */
enum class GameState {
  kGameNotStarted,
  kBeforeSpacePressed,
  kPowerAccumulating,
  kBallReleased,
  kGameHasFinished
};

/**
 * A class which represents the game itself, including the basketball, all the shooting mechanics, score, timer and
 * other features.
 */
class Shooter {
 public:
  const double kPI = 3.14159265;

  const size_t kWindowWidth = 1300;
  const size_t kWindowHeight = 700;
  const size_t kBackboardX = 1200; //The X coordinate of the backboard
  const size_t kBackboardYTop = 250; //The top of the backboard
  const size_t kBackboardYBottom = 300; //The bottom of the backboard
  const size_t kRimLeftEdge = 1140; //The left edge of the rim
  const size_t kRimRightEdge = 1200; //The right edge of the rim
  const size_t kOuterPowerRectBottomRight = 600;

  /**
   * A constructor for the shooter class. The variables are initialized here.
   */
  Shooter();

  /**
   * Advances one frame forward in the game.
   */
  void AdvanceOneFrame();

  /**
   * Displays all the elements of the game, including the basketball, score, timer, power knob and hoop
   */
  void Display();

  /**
   * Getter for the velocity parts vector used in the private helper method CalculateVelocityChangeWithAngle.
   * @return The velocity parts vector.
   */
  const glm::vec2& GetVelocityParts() const;

  /**
   * Getter for the basketball
   * @return the basketball
   */
  const Basketball& GetBasketball() const;

  /**
   * Getter for the GameState stored by this class
   * @return The GameState object
   */
  const GameState& GetState() const;

  /**
   * Getter for the power of the ball's release
   * @return the power of the ball's release
   */
  const int& GetPower() const;

  /**
   * Getter for the user's score
   * @return The user's score
   */
  const size_t& GetScore() const;

  /**
   * Getter for the Boolean representing whether the ball hit the backboard. This is used only for testing this
   * functionality.
   * @return The boolean regarding if the ball hit the backboard.
   */
  const bool& Get_Backboard_Boolean() const;

  /**
   * Getter for the timer. This is used for testing as well.
   * @return The timer
   */
  const ci::Timer& Get_Timer() const;

  /**
   * Setter for the GameState object.
   * @param state The new value for the GameState.
   */
  void SetState(GameState state);

  /**
   * Setter for the power.
   * @param power The new value for the power
   */
  void SetPower(int power);

  /**
   * Setter for the boolean regarding if the score has already been implemented. This is used in shooting_simulator.cpp.
   * @param score_already_incremented The new value for the boolean score_already_implemented_.
   */
  void SetScoreIncreasingBoolean(bool score_already_incremented);

  /**
   * Change the position of the basketball from a 2 pointer to a 3 pointer and vice-versa.
   * @param shooting_position Takes in a value of either 2 or 3, representing the next destination.
   */
  void ChangeBasketballPosition(int shooting_position);

  /**
   * Changes the angle of elevation of the ball
   * @param key_of_angle A value from 1-9 representing the angle of elevation in degrees / 10.
   */
  void ChangeAngle(int key_of_angle);

  /**
   * Change the Velocity of the ball using the power variable.
   */
  void ChangeBallVelocityFromPower();

  /**
   * Accumulate power as the user holds down the space bar.
   */
  void AccumulatePower();

  /**
   * Bounce the ball off the backboard by switching the direction of the x component of the velocity of the ball.
   */
  void BounceOffBackboard();

  /**
   * Increase the score if the ball goes through the hoop
   * @param score The increment to the score_ variable
   */
  void IncreaseScore(int score);

  /**
   * Starts the timer
   */
  void StartTime();

  /**
   * Ends the game if the timer has reached 1 minute
   */
  void EndGame();

  /**
   * Resets the variables from this class to their original values
   */
  void Reset();

 private:
  glm::vec2 velocity_parts_;
  GameState state_;
  glm::vec2 current_position_;
  glm::vec2 current_velocity_;
  glm::vec2 initial_position_;
  bool has_ball_bounced_off_backboard_;
  size_t score_;
  int power_;
  bool score_already_incremented_;
  Basketball ball_;
  ci::Timer timer_;

  /**
   * Calculates the change in the velocity of the ball through a change in the angle
   * @param total_velocity The total velocity of the ball (Calculated by taking the square root of the squared
   * individual components of the velocity)
   * @param angle The angle of elevation
   * @return The new velocity vector representing the changed velocity based on the angle
   */
  glm::vec2 CalculateVelocityChangeWithAngle(double total_velocity, double angle);
};
}
