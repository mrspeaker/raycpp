#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>

#include "GameMap.h"
#include "Player.h"

class GameManager {
 public:
    GameMap map;
    Player player;
    std::vector<Player> peeps;
    uint8_t gameState;

    GameManager();
    void populate();
    void update(float dt);
};

#endif // GAME_MANAGER_H
