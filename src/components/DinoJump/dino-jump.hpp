#pragma once

#include "./components/Menu/menu.hpp"
#include "./components/Navigation/navigation.hpp"
#include "./components/Game/game.hpp"

#include <stdint.h>

class DinoJump
{
public:
  DinoJump();

  void start();                                  // start class. Render menu and init interrupt callbacks
  void calculate_movement(int16_t x, int16_t y); // calculate movement based on x and y
  void start_game();                             // start the game
  void next();                                   // press next button
  void prev();                                   // press prev button

  static void on_EXTI4(); // prev interrupt callback
  static void on_EXTI5(); // next interrupt callback

private:
  static Menu menu;      // menu class
  Navigation navigation; // navigation class
  Game game;             // game class

  bool is_game_started = false; // flag to check if the game has started
};

extern DinoJump dino_jump;