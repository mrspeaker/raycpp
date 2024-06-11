#include "GameManager.h"

#include <raylib-cpp.hpp>
#include "globals.h"

GameManager::GameManager()=default;

void GameManager::populate() {
    for (int i = 0; i < 28; i++) {
        Player p(0.0, 0.0 + (i * 16.0));
        p.vel.x = GetRandomValue(40, 60) / 100.0;
        p.anim.speed = (1.0 - p.vel.x) * 0.2;
        p.anim.num_frames = 8;
        peeps.push_back(p);
    }
}

void GameManager::update(float dt) {
    for (Player &p : peeps) {
        p.update(dt);
        if (p.pos.x > screenWidth) p.pos.x = 0;
    }
}
