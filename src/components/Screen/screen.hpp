#pragma once

#include <stdint.h>

struct ChangeBinding
{
  int16_t *value;
  int16_t min;
  int16_t max;
  int16_t step;
  void (*onCommit)(int16_t newValue);
};

struct MenuItem
{
  const char *title;
  void (*onEnter)();
  const MenuItem *children;
  const ChangeBinding *change;
  uint8_t childCount;
};

class Screen
{
public:
  Screen(const MenuItem *root, uint8_t rootCount);

  void next();
  void prev();
  void up();
  void down();
  void render() const;

  void check(uint16_t x, uint16_t y); // move to joyDir
  void enter();                       // move to interrupt
  void back();                        // move to interrupt

  const char *currentTitle() const;

private:
  struct Level
  {
    const MenuItem *items;
    uint8_t count;
    uint8_t index;
  };

  static constexpr uint8_t kMaxDepth = 5;

  const MenuItem *currentItems;
  uint8_t currentCount;
  uint8_t currentIndex;
  uint8_t depth;
  Level stack[kMaxDepth];
};

extern Screen screen;
