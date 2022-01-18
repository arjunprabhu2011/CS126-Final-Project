#include "shooter.h"

namespace basketballgame {

Shooter::Shooter() : velocity_parts_(0, 0), ball_(glm::vec2(100, 600),
                                                  glm::vec2(0, 0), 0), timer_() {
  current_position_ = ball_.GetPosition();
  current_velocity_ = ball_.GetVelocity();
  initial_position_ = ball_.GetPosition();
  state_ = GameState::kGameNotStarted;
  //Initially sets the power to 600, which is the y component of the bottom right of the power rectangle knob
  power_ = 600;
  score_ = 0;
  score_already_incremented_ = false;
  has_ball_bounced_off_backboard_ = false;
};

glm::vec2 Shooter::CalculateVelocityChangeWithAngle(double total_velocity, double angle) {
  //Calculates the change in velocity from an angle using trigonometry
  velocity_parts_.x = total_velocity * cos(kPI * angle/180);
  velocity_parts_.y = -(total_velocity * sin(kPI * angle/180));
  return velocity_parts_;
}

void Shooter::AdvanceOneFrame() {
  BounceOffBackboard();

  ball_.UpdateBasketballState();
  //Checks if the score can be increased if it has not already been increased in this given shot
  if (!score_already_incremented_) {
    if (initial_position_ == glm::vec2(100, 600)) {
      IncreaseScore(3);
    } else {
      IncreaseScore(2);
    }
  }
}

void Shooter::Display() {
  ball_.Display();
  ci::gl::color(ci::Color("black"));
  //Draws the rim and the backboard/pole
  ci::gl::drawLine(glm::vec2(kBackboardX, 600), glm::vec2(kBackboardX, 250));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge, 300), glm::vec2(kRimRightEdge, 300));
  //Draw out the crosses for the basketball net
  ci::gl::drawLine(glm::vec2(kRimLeftEdge, 300), glm::vec2(kRimLeftEdge + (kRimRightEdge - kRimLeftEdge)/3,320));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge, 320), glm::vec2(kRimLeftEdge + (kRimRightEdge - kRimLeftEdge)/3,340));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge, 340), glm::vec2(kRimLeftEdge + (kRimRightEdge - kRimLeftEdge)/3,360));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 20, 300), glm::vec2(kRimLeftEdge + 2*(kRimRightEdge - kRimLeftEdge)/3,320));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 20, 320), glm::vec2(kRimLeftEdge + 2*(kRimRightEdge - kRimLeftEdge)/3,340));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 20, 340), glm::vec2(kRimLeftEdge + 2*(kRimRightEdge - kRimLeftEdge)/3,360));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 40, 300), glm::vec2(kRimRightEdge,320));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 40, 320), glm::vec2(kRimRightEdge,340));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 40, 340), glm::vec2(kRimRightEdge,360));

  ci::gl::drawLine(glm::vec2(kRimLeftEdge, 320), glm::vec2(kRimLeftEdge + (kRimRightEdge - kRimLeftEdge)/3,300));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge, 340), glm::vec2(kRimLeftEdge + (kRimRightEdge - kRimLeftEdge)/3,320));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge, 360), glm::vec2(kRimLeftEdge + (kRimRightEdge - kRimLeftEdge)/3,340));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 20, 320), glm::vec2(kRimLeftEdge + 2*(kRimRightEdge - kRimLeftEdge)/3,300));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 20, 340), glm::vec2(kRimLeftEdge + 2*(kRimRightEdge - kRimLeftEdge)/3,320));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 20, 360), glm::vec2(kRimLeftEdge + 2*(kRimRightEdge - kRimLeftEdge)/3,340));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 40, 320), glm::vec2(kRimRightEdge,300));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 40, 340), glm::vec2(kRimRightEdge,320));
  ci::gl::drawLine(glm::vec2(kRimLeftEdge + 40, 360), glm::vec2(kRimRightEdge,340));


  ci::gl::drawStringCentered("Score: " + std::to_string(score_), glm::vec2(kWindowWidth/2, kWindowHeight*1/10), ci::Color("black"),
                             ci::Font("Helvetica Neue", 40));

  ci::Rectf timer_rect(glm::vec2(0, 0), glm::vec2(500, 100));
  ci::gl::drawStrokedRect(timer_rect);
  ci::gl::drawStringCentered("Time: " + std::to_string(60 - timer_.getSeconds()), glm::vec2(150, 40), ci::Color("black"),
                             ci::Font("Helvetica Neue", 30));

  //The first rectangle is the outer power rectangle, while the second is the inner, shaded power rectangle
  ci::Rectf power_rect(glm::vec2(1230, 450), glm::vec2(1270, 600));
  ci::gl::drawStrokedRect(power_rect);

  ci::Rectf shooting_power(glm::vec2(1230, power_), glm::vec2(1270, 600));
  ci::gl::drawSolidRect(shooting_power);


  if (state_ == GameState::kGameNotStarted) {
    ci::gl::drawStringCentered("Click 's' to start the game!",glm::vec2(kWindowWidth/2, kWindowHeight*3/10),
                               ci::Color("black"),
                               ci::Font("Helvetica Neue", 30));
    ci::gl::drawStringCentered("Shoot the ball by holding down the space bar",glm::vec2(kWindowWidth/2, kWindowHeight*4/10),
                               ci::Color("black"),
                               ci::Font("Helvetica Neue", 30));
    ci::gl::drawStringCentered("Change the angle through the number keys",glm::vec2(kWindowWidth/2, kWindowHeight*1/2),
                               ci::Color("black"),
                               ci::Font("Helvetica Neue", 30));
  }


  if (state_ == GameState::kGameHasFinished) {
    ci::gl::drawStringCentered("Congratulations! You have finished the game. Click 'r' to play again", glm::vec2(kWindowWidth/2, kWindowHeight*3/10), ci::Color("black"),
                               ci::Font("Helvetica Neue", 30));
  }
}

void Shooter::ChangeBasketballPosition(int shooting_position) {
  //Changes the position of the ball to two and three point line accordingly
  if (shooting_position == 2) {
    ball_.SetPosition(glm::vec2(current_position_.x + 400, current_position_.y));
    ball_.SetVelocity(current_velocity_);
    initial_position_ = ball_.GetPosition();
  } else if (shooting_position == 3) {
    ball_.SetPosition(current_position_);
    ball_.SetVelocity(current_velocity_);
    initial_position_ = ball_.GetPosition();
  }
}

void Shooter::ChangeAngle(int key_of_angle) {
  //Changes the velocity of the ball based on the angle
  ball_.SetAngle(key_of_angle * 10);
  double total_ball_velocity = sqrt(pow(ball_.GetVelocity().x, 2) + pow(ball_.GetVelocity().y, 2));
  ball_.SetVelocity(CalculateVelocityChangeWithAngle(total_ball_velocity, ball_.GetAngle()));
  current_velocity_ = ball_.GetVelocity();
}

void Shooter::AccumulatePower() {
  //Lowers the power variable so because the top left corner of the inner power rectangle must go "down" in y coordinates.
  //This is because the (0,0) point is at the top left of the window.
  power_ -= 5;
  //If statement checking whether the power, or the height of the inner rectangle, matches the height of the outer rectangle.
  // If this is the case, the inner rectangle's height goes back the 0.
  if (power_ == 450) {
    power_ = kOuterPowerRectBottomRight;
  }
}

void Shooter::ChangeBallVelocityFromPower() {
  //Changes the x component of the ball's velocity by the difference in heights of the outer and inner power rectangles/2.
  //Changes the y component of the ball's velocity by the negation of the difference in the heights of the outer and inner power rectangles.
  ball_.SetVelocity(glm::vec2((600 - power_)/2, -(600 - power_)));
}

void Shooter::BounceOffBackboard() {
  //Checks if the ball is at the position of the backboard and bounces the ball off
  if (kBackboardX - ball_.GetPosition().x <= ball_.kBallRadius && ball_.GetPosition().y + ball_.kBallRadius >= kBackboardYTop
  && ball_.GetPosition().y - ball_.kBallRadius <= kBackboardYBottom) {
    ball_.SetVelocity(glm::vec2(-(ball_.GetVelocity().x), ball_.GetVelocity().y));
    has_ball_bounced_off_backboard_ = true;
  }
}

void Shooter::IncreaseScore(int score) {
  //Increases the score by a given amount if the ball goes through the hoop
  //Includes the 50 and the 2*radius in the if statement because cinder is not a completely continuous function in terms
  //of movement. Those values are to offset this fact and increment the score if the ball truly goes through the hoop
  if (ball_.GetVelocity().y >= 0 && ball_.GetPosition().x >= kRimLeftEdge &&
  ball_.GetPosition().x <= kRimRightEdge + 50 && abs(kBackboardYBottom - ball_.GetPosition().y) <= 2*ball_.kBallRadius) {
    score_ += score;
    score_already_incremented_ = true;
  }
}

void Shooter::StartTime() {
  //Starts timer
  timer_.start();
  state_ = GameState::kBeforeSpacePressed;
}

void Shooter::EndGame() {
  //Ends game
  if (timer_.getSeconds() >= 60) {
    timer_.stop();
    state_ = GameState::kGameHasFinished;
  }
}

void Shooter::Reset() {
  //Resets variables to original states
  ball_.SetPosition(glm::vec2(100, 600));
  ball_.SetVelocity(glm::vec2(0, 0));
  current_position_ = ball_.GetPosition();
  current_velocity_ = ball_.GetVelocity();
  initial_position_ = ball_.GetPosition();
  velocity_parts_ = glm::vec2(0, 0);
  state_ = GameState::kGameNotStarted;
  power_ = 600;
  score_ = 0;
  score_already_incremented_ = false;
}

const glm::vec2 & Shooter::GetVelocityParts() const {
  return velocity_parts_;
}

const size_t &Shooter::GetScore() const {
  return score_;
}

const int& Shooter::GetPower() const {
  return power_;
}

const Basketball& Shooter::GetBasketball() const {
  return ball_;
}

const GameState& Shooter::GetState() const {
  return state_;
}

const bool &Shooter::Get_Backboard_Boolean() const {
  return has_ball_bounced_off_backboard_;
}

const ci::Timer &Shooter::Get_Timer() const {
  return timer_;
}

void Shooter::SetScoreIncreasingBoolean(bool score_already_incremented) {
  score_already_incremented_ = score_already_incremented;
}

void Shooter::SetState(GameState state) {
  state_ = state;
}

void Shooter::SetPower(int power) {
  power_ = power;
}

}
