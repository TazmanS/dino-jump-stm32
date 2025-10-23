#include "screen-config.hpp"
#include "screen-actions.hpp"

int16_t default_difficulty = 3;
int16_t default_sound = 25;

int16_t menu_length = 3;

const MenuItem root_items[] = {
    {"Start", start_action, nullptr, nullptr, 0},
    {"About", about_action, nullptr, nullptr, 0},
    {"Settings", settings_action,
     (MenuItem[]){
         {"Difficulty", nullptr, nullptr, (ChangeBinding[]){&default_difficulty, 0, 10, 1, save_difficulty}, 0},
         {"Sound", nullptr, nullptr, (ChangeBinding[]){&default_sound, 0, 100, 10, save_sound}, 0}},
     nullptr, 2},
};