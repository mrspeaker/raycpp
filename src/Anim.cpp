#include "Anim.h"

Anim::Anim() {};
void Anim::update(float dt) {
    time += dt;
    if (time > speed) {
        time -= speed;
        frame += 1;
        if (frame > num_frames) {
            frame = 0;
        }
    }

};
