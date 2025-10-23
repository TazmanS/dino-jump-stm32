#include "screen.hpp"
#include "screen-config.hpp"
#include "lcd.hpp"

Screen::Screen(const MenuItem *root, uint8_t root_count)
    : current_items{root},
      current_count{root_count},
      current_index{0},
      depth{0}
{
}

void Screen::next()
{
  if (!current_count)
    return;
  current_index = (uint8_t)((current_index + 1) % current_count);

  render();
};
void Screen::prev()
{
  if (!current_count)
    return;

  current_index = (current_index == 0) ? (uint8_t)(current_count - 1) : (uint8_t)(current_index - 1);

  render();
};

void Screen::up() {};
void Screen::down() {};

void Screen::check(uint16_t adc_x, uint16_t y)
{
  static bool was_pressed = false;
  if ((adc_x > 3000) & !was_pressed)
  {
    screen.next();

    was_pressed = true;
  }
  else if ((adc_x < 500) & !was_pressed)
  {
    screen.prev();

    was_pressed = true;
  }
  else if ((adc_x < 2500) & (adc_x > 1500))
  {
    was_pressed = false;
  }
}

void Screen::enter() {};
void Screen::back() {};

void Screen::render() const
{
  display_clear();
  display_print(current_title());
};

const char *Screen::current_title() const
{
  return current_items[current_index].title;
};

Screen screen(root_items, menu_length);