#pragma once

#include "./components/Menu/menu.hpp"
#include "./components/Navigation/navigation.hpp"

#include <stdint.h>

class DinoJump
{
public:
  DinoJump();

  void start();
  void calculateMovement(int16_t x, int16_t y);

private:
  Menu menu;
  Navigation navigation;

  bool is_game_start = false;

  void moveMenu(Direction direction);
};

extern DinoJump dino_jump;