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

uint8_t Screen::count() const
{
  return (uint8_t)(sizeof currentItems) / (sizeof currentItems[0]);
};

uint8_t Screen::index() const
{
  return currentIndex;
};

static constexpr MenuItem rootItems[] = {
    {"Start", nullptr, nullptr, 0},
    {"About", nullptr, nullptr, 0},
    {"Settings", nullptr, nullptr, 0},
};

Screen screen(rootItems, (uint8_t)(sizeof rootItems) / (sizeof rootItems[0]));

// // ---- ВСПОМОГАТЕЛЬНОЕ ----
// static void noop() {}

// void Screen::next() {
//   if (!currentCount) return;
//   currentIndex = (uint8_t)((currentIndex + 1) % currentCount);
//   render();
// }

// void Screen::prev() {
//   if (!currentCount) return;
//   currentIndex = (currentIndex == 0) ? (uint8_t)(currentCount - 1)
//                                      : (uint8_t)(currentIndex - 1);
//   render();
// }

// void Screen::enter() {
//   if (!currentCount) return;
//   const MenuItem& it = currentItems[currentIndex];

//   if (it.children && it.childCount > 0) {
//     // есть подменю — заходим внутрь
//     if (depth < kMaxDepth) {
//       stack[depth] = { currentItems, currentCount, currentIndex };
//       depth++;
//     }
//     currentItems = it.children;
//     currentCount = it.childCount;
//     currentIndex = 0;
//     render();
//   } else {
//     // лист — вызываем действие (если есть)
//     (it.onEnter ? it.onEnter : noop)();
//     // Можно оставить на месте; при желании — render();
//   }
// }

// void Screen::back() {
//   if (depth == 0) return;
//   depth--;
//   currentItems = stack[depth].items;
//   currentCount = stack[depth].count;
//   currentIndex = stack[depth].index;
//   render();
// }

// const char* Screen::currentTitle() const {
//   return (currentCount ? currentItems[currentIndex].title : "");
// }

// uint8_t Screen::count() const { return currentCount; }
// uint8_t Screen::index() const { return currentIndex; }

// void Screen::render() const {
//   display_clear();
//   display_print(currentTitle());
// }

// // ---- ДЕЙСТВИЯ (ПРИМЕРЫ) ----
// static void actionStart() { /* старт игры / логика */ }
// static void actionInfo()  { /* показать версию / лог */ }
// static void actionReset() { /* сброс настроек */ }

// // ---- ПОДМЕНЮ (ПРИМЕРЫ) ----
// static constexpr MenuItem settingsItems[] = {
//   {"Brightness",  nullptr,      nullptr, 0},
//   {"Volume",      nullptr,      nullptr, 0},
//   {"Reset",       actionReset,  nullptr, 0},
// };

// static constexpr MenuItem aboutItems[] = {
//   {"Version",     actionInfo,   nullptr, 0},
//   {"License",     nullptr,      nullptr, 0},
// };

// // ---- КОРНЕВОЕ МЕНЮ ----
// static constexpr MenuItem rootItems[] = {
//   {"Start",    actionStart,   nullptr,        0},
//   {"Settings", nullptr,       settingsItems,  (uint8_t)(sizeof(settingsItems)/sizeof(settingsItems[0]))},
//   {"About",    nullptr,       aboutItems,     (uint8_t)(sizeof(aboutItems)/sizeof(aboutItems[0]))},
// };

// // ---- ГЛОБАЛЬНЫЙ ЭКЗЕМПЛЯР ----
// Screen screen(rootItems, (uint8_t)(sizeof(rootItems)/sizeof(rootItems[0])));

// // ---- ПРИМЕР ВЫЗОВОВ КНОПОК ----
// // где-то в коде:
// // void onBtnNext()  { screen.next();  }
// // void onBtnPrev()  { screen.prev();  }
// // void onBtnEnter() { screen.enter(); }
// // void onBtnBack()  { screen.back();  }