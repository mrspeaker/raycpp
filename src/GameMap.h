#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>

class GameMap {
 public:
    int tw;
    int th;
    std::vector<int> tiles;
    GameMap();
    void gen(int x, int y);
};


#endif // GAME_MAP_H
