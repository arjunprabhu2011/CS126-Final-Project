#include "basketball.h"

namespace basketballgame {

Basketball::Basketball(const glm::vec2 &position, const glm::vec2 &initial_velocity, double angle) {
  position_ = position;
  velocity_ = initial_velocity;
  angle_ = angle;
}

void Basketball::UpdateBasketballState() {
  //Changes the y component of the velocity and the position of the ball accordingly to create a parabolic path
  velocity_.y += kAcceleration;
  position_ += velocity_;
}

void Basketball::Display() const {
  ci::gl::color(ci::Color("orange"));
  ci::gl::drawSolidCircle(GetPosition(), kBallRadius);
}

const glm::vec2 &Basketball::GetPosition() const {
  return position_;
}

const glm::vec2 &Basketball::GetVelocity() const {
  return velocity_;
}

const double& Basketball::GetAngle() const {
  return angle_;
}

void Basketball::SetVelocity(const glm::vec2 &velocity) {
  velocity_ = velocity;
}

void Basketball::SetAngle(double angle) {
  angle_ = angle;
}

void Basketball::SetPosition(const glm::vec2 &position) {
  position_ = position;
}

} //namespace basketballgame
