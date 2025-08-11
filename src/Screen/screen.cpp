#include "screen.hpp"
#include "lcd.hpp"

Screen::Screen()
    : menuItems{"Start", "Settings", "About"},
      menuLength(sizeof(menuItems) / sizeof(menuItems[0])),
      menuIndex(0)
{
}

void Screen::next()
{
  menuIndex = (menuIndex + 1) % menuLength;

  display_clear();
  display_print(menuItems[menuIndex]);
}

void Screen::prev()
{
  if (menuIndex == 0)
    menuIndex = menuLength - 1;
  else
    menuIndex--;

  display_clear();
  display_print(menuItems[menuIndex]);
}

Screen screen;