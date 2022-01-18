#include <catch2/catch.hpp>
#include "basketball.h"
#include "shooter.h"

using basketballgame::Basketball;
using basketballgame::Shooter;
using basketballgame::GameState;

TEST_CASE("Ball's Velocity changes with power") {
  Shooter shooter_;
  shooter_.SetPower(550);
  shooter_.ChangeBallVelocityFromPower();
  REQUIRE(shooter_.GetBasketball().GetVelocity() == glm::vec2(25, -50));
}

TEST_CASE("Calculate Velocity Change With Angle Works Properly") {
  Shooter shooter_;
  SECTION("Angle is 10 degrees") {
    shooter_.SetPower(550);
    shooter_.ChangeBallVelocityFromPower();
    shooter_.ChangeAngle(1);
    REQUIRE(shooter_.GetBasketball().GetVelocity() == glm::vec2(55.052427012603, -9.7072282358055));
  }

  SECTION("Angle is 90 degrees") {
    shooter_.SetPower(550);
    shooter_.ChangeBallVelocityFromPower();
    shooter_.ChangeAngle(9);
    REQUIRE(shooter_.GetBasketball().GetVelocity().x + 1 == Approx(1));
    REQUIRE(shooter_.GetBasketball().GetVelocity().y == Approx(-55.901699437495));
  }

  SECTION("Angle is somewhere between 10 degrees and 90 degrees") {
    shooter_.SetPower(550);
    shooter_.ChangeBallVelocityFromPower();
    shooter_.ChangeAngle(6);
    REQUIRE(shooter_.GetBasketball().GetVelocity().x == Approx(27.9508));
    REQUIRE(shooter_.GetBasketball().GetVelocity().y == Approx(-48.4123));
  }
}

TEST_CASE("Angle stays the same as the GameState changes unless the user clicks a number key") {
  Shooter shooter_;
  shooter_.ChangeAngle(6);
  shooter_.SetState(GameState::kBeforeSpacePressed);
  REQUIRE(shooter_.GetBasketball().GetAngle() == 60);
  shooter_.SetState(GameState::kPowerAccumulating);
  REQUIRE(shooter_.GetBasketball().GetAngle() == 60);
  shooter_.SetState(GameState::kBallReleased);
  REQUIRE(shooter_.GetBasketball().GetAngle() == 60);
  shooter_.SetState(GameState::kBeforeSpacePressed);
  REQUIRE(shooter_.GetBasketball().GetAngle() == 60);
}

TEST_CASE("Score increments properly") {
  Shooter shooter_;
  SECTION("Score doesn't increment if the ball is not at the position of the hoop") {
    REQUIRE(shooter_.GetScore() == 0);
    shooter_.IncreaseScore(3);
    REQUIRE(shooter_.GetScore() == 0);
    shooter_.IncreaseScore(2);
    REQUIRE(shooter_.GetScore() == 0);
  }

  SECTION("Score increments if the ball is moved to the position of the hoop and doesn't keep incrementing") {
    REQUIRE(shooter_.GetScore() == 0);
    shooter_.SetPower(490);
    shooter_.ChangeBallVelocityFromPower();
    shooter_.ChangeAngle(5);
    //For this for loop, I ran the actual game and found one precise angle and power that causes the ball to go into
    //the hoop. This for loop simply moves the ball to the hoop using the AdvanceOneFrame method.
    for (size_t i = 0; i < 17; i++) {
      shooter_.AdvanceOneFrame();
    }

    REQUIRE(shooter_.GetScore() == 3);
    shooter_.AdvanceOneFrame();
    REQUIRE(shooter_.GetScore() == 3);
  }
}

TEST_CASE("The GameState enum changes accordingly") {
  Shooter shooter_;
  SECTION("The state starts at kGameNotStarted") {
    REQUIRE(shooter_.GetState() == GameState::kGameNotStarted);
  }

  SECTION("The state changes when the timer starts") {
    shooter_.StartTime();
    REQUIRE(shooter_.GetState() == GameState::kBeforeSpacePressed);
  }
}

TEST_CASE("Ball bounces off backboard") {
  Shooter shooter_;
  shooter_.SetPower(480);
  shooter_.ChangeBallVelocityFromPower();
  shooter_.ChangeAngle(4);
  //For this for loop, I ran the actual game and found one precise angle and power that causes the ball to bounce off
  //the backboard. This for loop simply moves the ball to the backboard using the AdvanceOneFrame method.
  for (size_t i = 0; i < 18; i++) {
    shooter_.AdvanceOneFrame();
  }

  REQUIRE(shooter_.Get_Backboard_Boolean() == true);
}

TEST_CASE("Change basketball's position from 2 to 3 and vice versa") {
  Shooter shooter_;
  SECTION("Change basketball's position from a 3 pointer to a 2 pointer") {
    shooter_.ChangeBasketballPosition(2);
    REQUIRE(shooter_.GetBasketball().GetPosition() == glm::vec2(500, 600));
  }

  SECTION("Change basketball's position from a 2 pointer to a 3 pointer") {
    shooter_.ChangeBasketballPosition(2);
    REQUIRE(shooter_.GetBasketball().GetPosition() == glm::vec2(500, 600));
    shooter_.ChangeBasketballPosition(3);
    REQUIRE(shooter_.GetBasketball().GetPosition() == glm::vec2(100, 600));
  }
}

TEST_CASE("Power accumulates properly") {
  Shooter shooter_;
  shooter_.AccumulatePower();
  shooter_.AccumulatePower();
  shooter_.AccumulatePower();
  REQUIRE(shooter_.GetPower() == 585);
}

TEST_CASE("Start time method works properly") {
  Shooter shooter_;
  shooter_.StartTime();
  REQUIRE(shooter_.Get_Timer().isStopped() == false);
}

TEST_CASE("Reset method works properly") {
  Shooter shooter_;
  shooter_.Reset();
  REQUIRE(shooter_.GetBasketball().GetPosition() == glm::vec2(100, 600));
  REQUIRE(shooter_.GetBasketball().GetVelocity() == glm::vec2(0, 0));
  REQUIRE(shooter_.GetState() == GameState::kGameNotStarted);
  REQUIRE(shooter_.GetVelocityParts() == glm::vec2(0, 0));
  REQUIRE(shooter_.GetPower() == 600);
  REQUIRE(shooter_.GetScore() == 0);
}



