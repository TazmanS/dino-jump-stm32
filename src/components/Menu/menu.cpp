#include "menu.hpp"
#include "menu-config.hpp"
#include "lcd.hpp"

Menu::Menu(const MenuItem *root, uint8_t root_count)
    : current_items{root},
      current_count{root_count},
      current_index{0},
      depth{0}
{
}

void Menu::next() {};

void Menu::prev() {};

void Menu::up()
{
  if (!current_count)
    return;

  current_index = (current_index == 0) ? (uint8_t)(current_count - 1) : (uint8_t)(current_index - 1);

  render();
};

void Menu::down()
{
  if (!current_count)
    return;
  current_index = (uint8_t)((current_index + 1) % current_count);

  render();
};

void Menu::render() const
{
  display_clear();
  display_print(current_title());
};

const char *Menu::current_title() const
{
  return current_items[current_index].title;
};