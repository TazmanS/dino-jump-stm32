#include "interrupts.hpp"
#include "usart.hpp"
#include "./dino-jump.hpp"

#include "./components/Menu/menu.hpp"
#include "./components/Menu/menu-config.hpp"

#include "defines.hpp"

DinoJump::DinoJump() : navigation() {};

Menu DinoJump::menu(root_items, menu_length);

void DinoJump::start()
{
  menu.render();

  EXTI5_callback(&DinoJump::onExti5);
  EXTI4_callback(&DinoJump::onExti4);
};

void DinoJump::onExti4()
{
  dino_jump.prev();
}

void DinoJump::onExti5()
{
  dino_jump.next();
}

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
    case Direction::LEFT:
      menu.left();
      break;
    case Direction::RIGHT:
      menu.right();
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

void DinoJump::prev()
{
  menu.prev();

  usart_send_str("EXTI4_IRQHandler, prev \r\n");
}

void DinoJump::next()
{
  menu.next();

  usart_send_str("EXTI5_IRQHandler, next \r\n");
}

DinoJump dino_jump;