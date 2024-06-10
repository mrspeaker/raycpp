#include <raylib-cpp.hpp>
#include <iostream>
#include <vector>
#include "globals.h"
#include "Player.h"
#include "Anim.h"
#include "GameManager.h"
#include "RendererRayLib.h"

int main() {

    raylib::Window w(screenWidth, screenHeight, "Raycpp");
    SetTargetFPS(60);

    RendererRayLib renderer{};
    GameManager gm;

    gm.populate();

    while (!w.ShouldClose())
    {
        auto dt = GetFrameTime();
        gm.update(dt);
        renderer.render(gm);
    }

    return 0;
}
