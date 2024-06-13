#include <raylib-cpp.hpp>
#include "Player.h"

Player::Player():GameObject() {};
Player::Player(float x, float y): GameObject(x, y) {};

void Player::update(float dt) {
    if (GetRandomValue(0, 100) == 1) {
        vel.x += GetRandomValue(-20, 20) / 100.0;
        if (vel.x < 0.2) vel.x = 0.2;
        if (vel.x > 0.3) vel.x -= 0.08;
        anim.speed = (1.0 - vel.x) * 0.2;
    }

    GameObject::update();
    anim.update(dt);
}
