#include "GameMap.h"

#include <math.h>
#include <raylib-cpp.hpp>

GameMap::GameMap()=default;

void GameMap::gen(int w, int h) {
    tw = w;
    th = h;
    tiles.resize(w * h);

    for (int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            tiles[y * w + x] = abs(
                cosf((double)x / 5.0) *
                sinf((double)y / 4.0)) * 4;
            if (tiles[y * w + x] > 4) {
                tiles[y * w + x] = 0;
            }
        }
    }
};
