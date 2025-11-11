#pragma once

#include "stdint.h"

class Player
{
public:
  Player(uint8_t health);
  void render();
  void jump();

  uint8_t get_health() const;

private:
  uint8_t health;
  bool is_jumped;
};