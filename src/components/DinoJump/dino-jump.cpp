#include "./dino-jump.hpp"

#include "./components/Menu/menu.hpp"
#include "./components/Menu/menu-config.hpp"

DinoJump::DinoJump() : menu(root_items, menu_length), navigation() {};

void DinoJump::start()
{
  menu.render();
};

void DinoJump::calculateMovement(int16_t x, int16_t y)
{
  auto [dx, dy] = navigation.getParams(x, y);

  if (is_game_start)
  {
  }
  else
  {
    // MOVE TO ONE METHOD
    switch (dx)
    {
    case Direction::PREV:
      menu.prev();
      break;
    case Direction::NEXT:
      menu.next();
      break;
    }

    switch (dy)
    {
    case Direction::UP:
      menu.up();
      break;
    case Direction::DOWN:
      menu.down();
      break;
    }
  }
};

DinoJump dino_jump;