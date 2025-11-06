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

  EXTI5_callback(&DinoJump::on_EXTI5);
  EXTI4_callback(&DinoJump::on_EXTI4);
};

void DinoJump::on_EXTI4()
{
  dino_jump.prev();
}

void DinoJump::on_EXTI5()
{
  dino_jump.next();
}

void DinoJump::calculate_movement(int16_t x, int16_t y)
{
  auto [dx, dy] = navigation.getParams(x, y);

  if (is_game_started)
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

void DinoJump::start_game()
{
  dino_jump.is_game_started = true;
}

DinoJump dino_jump;