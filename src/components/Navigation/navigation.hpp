#pragma once

#include <stdint.h>
#include <utility>

enum class Direction
{
  LEFT,
  RIGHT,
  UP,
  DOWN,
  CENTER
};

class Navigation
{
public:
  Navigation();

  std::pair<Direction, Direction> getParams(int16_t x, int16_t y);
};
