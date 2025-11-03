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
  void next();
  void prev();

  static void onExti4(); // prev
  static void onExti5(); // next

private:
  static Menu menu;
  Navigation navigation;

  bool is_game_start = false;

  void moveMenu(Direction direction);
};

extern DinoJump dino_jump;