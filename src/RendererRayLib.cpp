#include "globals.h"
#include "RendererRayLib.h"
#include <raylib-cpp.hpp>
#include <iostream>


RendererRayLib::RendererRayLib() {
    tex.Load("res/walk.png");
    text_col = raylib::Color::Gray();
    rec = { 0.0f, 0.0f, 16.0, 16.0 };
}

void RendererRayLib::render(const GameManager &gm) {
    // Draw
    BeginDrawing();
    ClearBackground(BLACK);
    raylib::Color g(DARKGRAY);
    text_col.DrawText("Werd, Up!", 190, 200, 20);

    if (IsGamepadAvailable(0)) {
        DrawCircle(259 + (int)(GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X)*20),
                   152 + (int)(GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)*20), 20, RAYWHITE);

        DrawCircle(459 + (int)(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X)*20),
                   152 + (int)(GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y)*20), 20, RAYWHITE);
    }

    for (const Player &p : gm.peeps) {
        rec.x = p.anim.frame * 16.0;
        tex.Draw(rec, p.pos, RAYWHITE);
    }

    EndDrawing();
};
