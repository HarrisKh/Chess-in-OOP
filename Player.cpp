#include "Player.h"

Player::Player(string n, COLOR c) :name(n), color(c) {}

string Player::getName() const
{
    return name;
}

COLOR Player::getColor() const
{
    return color;
}

