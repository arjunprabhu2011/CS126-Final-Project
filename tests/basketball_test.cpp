#include <catch2/catch.hpp>
#include "basketball.h"
#include "shooter.h"

using basketballgame::Basketball;
using basketballgame::Shooter;
using basketballgame::GameState;

TEST_CASE("Basketball's Motion Changes Accurately When Initial Velocity Is 0") {
  Basketball ball(glm::vec2(100, 100), glm::vec2(0, 0), 0);
  SECTION("Basketball velocity changes properly") {
    ball.UpdateBasketballState();
    REQUIRE(ball.GetVelocity() == glm::vec2(0, 9.8));
  }

  SECTION("Basketball's position changes properly") {
    ball.UpdateBasketballState();
    REQUIRE(ball.GetPosition() == glm::vec2(100, 109.8));
  }
}

TEST_CASE("Basketball's Motion Changes Accurately When Initial Velocity Is Not 0") {
  Basketball ball(glm::vec2(100, 100), glm::vec2(10, 15), 0);
  SECTION("Basketball velocity changes properly") {
    ball.UpdateBasketballState();
    REQUIRE(ball.GetVelocity() == glm::vec2(10, 24.8));
  }

  SECTION("Basketball's position changes properly") {
    ball.UpdateBasketballState();
    REQUIRE(ball.GetPosition() == glm::vec2(110, 124.8));
  }
}
