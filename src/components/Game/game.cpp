#include "./game.hpp"
#include "lcd.hpp"

/*
   ________________
  |Hx3       s:9999|
  |   P E   E   E  |
  |________________|
*/

Game::Game() : player(default_health) {};

void Game::init()
{
  player = Player(default_health);

  show_health();

  show_score();
};

void Game::show_health() const
{
  lcd_set_cursor(0, 0);

  for (uint8_t i = 0; i < player.get_health(); i++)
  {
    lcd_send_data(HEART_INDEX);
  };
};

void Game::show_score() const
{
  lcd_set_cursor(0, 10);
  display_print("S:");
  display_uint(score);
};
