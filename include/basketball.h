#pragma once
#include <cinder/gl/gl.h>
#include <cinder/Timer.h>

namespace basketballgame {

/**
 * A class which represents the basketball in the game.
 */
class Basketball {
 public:
  constexpr static double kAcceleration = 9.8;
  const double kBallRadius = 10;

  /**
   * Constructor for the Basketball class
   * @param position         The position vector for the basketball
   * @param initial_velocity The initial velocity vector for the basketball
   * @param angle            The angle of elevation for the ball.
   */
  Basketball(const glm::vec2& position, const glm::vec2& initial_velocity, double angle);

  //Getters for the private variables
  const glm::vec2& GetPosition() const;
  const glm::vec2& GetVelocity() const;
  const double& GetAngle() const;

  /**
   * Updates the position and velocity vectors of the ball to create a projectile motion
   */
  void UpdateBasketballState();

  /**
   * Displays the basketball to the GUI.
   */
  void Display() const;

  //Setters for velocity and the angle variables
  void SetPosition(const glm::vec2& position);
  void SetVelocity(const glm::vec2& velocity);
  void SetAngle(double angle);

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  double angle_;
};
}
