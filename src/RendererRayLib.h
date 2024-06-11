#ifndef RENDERER_RAYLIB_H
#define RENDERER_RAYLIB_H

#include <raylib-cpp.hpp>
#include "Renderer.h"
#include "GameManager.h"

class RendererRayLib : public Renderer {
 public:
    Rectangle rec;
    raylib::Texture peeps;
    raylib::Texture tiles;
    raylib::Color text_col;

    RendererRayLib();
    void render(const GameManager &gm) override;
    void render_tiles(const GameMap map);
};

#endif // RENDERER_H
