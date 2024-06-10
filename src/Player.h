#pragma once

#include "GameObject.h"
#include "Anim.h"

class Player : public GameObject {
 public:
    Player();
    Player(float x, float y);
    void update(float dt);
    float speed;
    Anim anim;
};
