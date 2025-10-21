#include "screen.hpp"
#include "lcd.hpp"

Screen::Screen(const MenuItem *root, uint8_t rootCount)
    : currentItems(root),
      currentCount(rootCount),
      currentIndex(0),
      depth(0)
{
}

void Screen::next()
{
  if (!currentCount)
    return;
  currentIndex = (uint8_t)((currentIndex + 1) % currentCount);

  render();
};
void Screen::prev()
{
  if (!currentCount)
    return;

  currentIndex = (currentIndex == 0) ? (uint8_t)(currentCount - 1) : (uint8_t)(currentIndex - 1);

  render();
};

void up() {};
void down() {};
void check(uint16_t adc_x, uint16_t y)
{
  static bool wasPressed = false;
  if ((adc_x > 3000) & !wasPressed)
  {
    screen.next();

    wasPressed = true;
  }
  else if ((adc_x < 500) & !wasPressed)
  {
    screen.prev();

    wasPressed = true;
  }
  else if ((adc_x < 2500) & (adc_x > 1500))
  {
    wasPressed = false;
  }
}

void Screen::enter() {};
void Screen::back() {};
void Screen::render() const
{
  display_clear();
  display_print(currentTitle());
};

const char *Screen::currentTitle() const
{
  return currentItems[currentIndex].title;
};

void startAction() {};

void aboutAction() {};

void settingsAction() {};

void saveDifficulty(int16_t newValue) {};

void saveSound(int16_t newValue) {};

int16_t default_difficulty = 3;
int16_t default_sound = 25;

static constexpr MenuItem rootItems[] = {
    {"Start", startAction, nullptr, nullptr, 0},
    {"About", aboutAction, nullptr, nullptr, 0},
    {"Settings", settingsAction,
     (MenuItem[]){
         {"Difficulty", nullptr, nullptr, (ChangeBinding[]){&default_difficulty, 0, 10, 1, saveDifficulty}, 0},
         {"Sound", nullptr, nullptr, (ChangeBinding[]){&default_sound, 0, 100, 10, saveSound}, 0}},
     nullptr, 2},
};

Screen screen(rootItems, (uint8_t)(sizeof rootItems) / (sizeof rootItems[0]));