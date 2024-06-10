#ifndef RENDERER_RAYLIB_H
#define RENDERER_RAYLIB_H

#include <raylib-cpp.hpp>
#include "Renderer.h"
#include "GameManager.h"

class RendererRayLib : public Renderer {
 public:
    Rectangle rec;
    raylib::Texture tex;
    raylib::Color text_col;

    RendererRayLib();
    void render(const GameManager &gm) override;
};

#endif // RENDERER_H
