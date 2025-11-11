#include "./player.hpp"

Player::Player(uint8_t health) : health(health) {};

void Player::render() {};

void Player::jump() {};

uint8_t Player::get_health() const
{
  return health;
};