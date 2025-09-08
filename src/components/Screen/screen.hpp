#pragma once

#include <stdint.h>

class Screen
{
public:
  Screen();
  void next();
  void prev();

private:
  const char *menuItems[3];
  const uint8_t menuLength;
  volatile uint8_t menuIndex;
};

extern Screen screen;
