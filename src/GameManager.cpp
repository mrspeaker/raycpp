#include "GameManager.h"

#include <raylib-cpp.hpp>
#include "globals.h"

GameManager::GameManager()=default;

void GameManager::populate() {
    for (int i = 0; i < 28; i++) {
        Player p(0.0, 0.0 + (i * 16.0) - 1.0);
        p.vel.x = GetRandomValue(40, 60) / 100.0;
        p.anim.speed = 0.1;
        p.anim.num_frames = 8;
        peeps.push_back(p);
    }

    map.gen(screenWidth / 16, screenHeight / 16);
}

void GameManager::update(float dt) {
    for (Player &p : peeps) {
        p.update(dt);
        if (p.pos.x > screenWidth) p.pos.x = 0;
    }
}
