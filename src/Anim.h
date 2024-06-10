#pragma once

#include "GameObject.h"

class Anim {
public:
    Anim();
    void update(float dt);
    int frame;
    int num_frames;
    float time;
    float speed;
};
