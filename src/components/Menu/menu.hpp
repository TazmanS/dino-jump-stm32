#pragma once

#include "./components/Navigation/navigation.hpp"

#include <stdint.h>

struct ChangeBinding
{
  int16_t *value;
  int16_t min;
  int16_t max;
  int16_t step;
  void (*on_commit)(int16_t new_value);
};

struct MenuItem
{
  const char *title;
  void (*on_enter)();
  const MenuItem *children;
  const ChangeBinding *change;
  uint8_t child_count;
};

class Menu
{
public:
  Menu(const MenuItem *root, uint8_t root_count);

  void next();
  void prev();
  void up();
  void down();
  void render() const;

  const char *current_title() const;

private:
  struct Level
  {
    const MenuItem *items;
    uint8_t count;
    uint8_t index;
  };

  static constexpr uint8_t k_max_depth = 5;

  const MenuItem *current_items;
  uint8_t current_count;
  uint8_t current_index;
  uint8_t depth;
  Level stack[k_max_depth];
};
