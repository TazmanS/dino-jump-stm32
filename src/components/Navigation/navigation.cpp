#include "./navigation.hpp"

const int UP_TOGGLE_LINE = 3000;
const int DOWN_TOGGLE_LINE = 500;
const int CENTER_UP_LINE = 2500;
const int CENTER_DOWN_LINE = 1500;

Direction calculateDirectionX(int16_t x);
Direction calculateDirectionY(int16_t y);

Navigation::Navigation() {};

std::pair<Direction, Direction> Navigation::getParams(int16_t x, int16_t y)
{
  Direction direction_x = calculateDirectionX(x);
  Direction direction_y = calculateDirectionY(y);

  return {direction_x, direction_y};
};

Direction calculateDirectionX(int16_t x)
{
  Direction direction_x = Direction::CENTER;
  static bool was_pressed = false;
  if ((x > UP_TOGGLE_LINE) & !was_pressed)
  {
    direction_x = Direction::PREV;

    was_pressed = true;
  }
  else if ((x < DOWN_TOGGLE_LINE) & !was_pressed)
  {
    direction_x = Direction::NEXT;

    was_pressed = true;
  }
  else if ((x < CENTER_UP_LINE) & (x > CENTER_DOWN_LINE))
  {
    was_pressed = false;
  }

  return direction_x;
};

Direction calculateDirectionY(int16_t y)
{
  Direction direction_y = Direction::CENTER;
  static bool was_pressed = false;
  if ((y > UP_TOGGLE_LINE) & !was_pressed)
  {
    direction_y = Direction::UP;

    was_pressed = true;
  }
  else if ((y < DOWN_TOGGLE_LINE) & !was_pressed)
  {
    direction_y = Direction::DOWN;

    was_pressed = true;
  }
  else if ((y < CENTER_UP_LINE) & (y > CENTER_DOWN_LINE))
  {
    was_pressed = false;
  }

  return direction_y;
};