#pragma once

#include "../Player/player.hpp"

class Game
{
public:
  Game();
  void init();

private:
  Player player;
  // enemies class []

  uint8_t default_health = 3;
  uint16_t score = 0;

  void show_health() const;
  void show_score() const;
};