#include <raylib-cpp.hpp>
#include "Player.h"

Player::Player():GameObject() {};
Player::Player(float x, float y): GameObject(x, y) {};

void Player::update(float dt) {
    GameObject::update();
    anim.update(dt);
}
