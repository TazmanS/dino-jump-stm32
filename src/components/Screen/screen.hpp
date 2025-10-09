#pragma once

#include <stdint.h>

struct MenuItem
{
  const char *title;
  void (*onEnter)();
  const MenuItem *children;
  uint8_t childCount;
};

class Screen
{
public:
  Screen(const MenuItem *root, uint8_t rootCount);

  void next();
  void prev();
  void enter();
  void back();
  void render() const;

  const char *currentTitle() const;
  uint8_t count() const; // TODO mb delete
  uint8_t index() const; // TODO mb delete

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
