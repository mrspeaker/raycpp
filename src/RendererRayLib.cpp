#include "globals.h"
#include "RendererRayLib.h"
#include <raylib-cpp.hpp>
#include <iostream>

RendererRayLib::RendererRayLib() {
    peeps.Load("res/walk.png");
    tiles.Load("res/tiles.png");

    text_col = raylib::Color::Gray();
    rec = { 0.0f, 0.0f, 16.0, 16.0 };
}

void RendererRayLib::render(const GameManager &gm) {
    // Draw
    //BeginDrawing();
    ClearBackground(BLACK);
    raylib::Color g(DARKGRAY);
    text_col.DrawText("Werd, Up!", 190, 200, 20);

    render_tiles(gm.map);

    for (const Player &p : gm.peeps) {
        rec.x = p.anim.frame * 16.0;
        peeps.Draw(rec, p.pos, RAYWHITE);
    }

    //EndDrawing();
};

void RendererRayLib::render_tiles(const GameMap map) {
    for (int y = 0; y < map.th; y++) {
        for(int x = 0; x < map.tw; x++) {
            auto tile = map.tiles[y * map.tw + x];
            if (tile > 0) {
                tiles.Draw((Rectangle){ 0.0, static_cast<float>(tile * 32), 16.0, 16.0 },
                           (Vector2) { (float)(x * 16), (float)(y * 16) }, RAYWHITE);
            }
        }
    }
}
