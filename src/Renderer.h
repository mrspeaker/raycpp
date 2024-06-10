#ifndef RENDERER_H
#define RENDERER_H

#include "GameManager.h"

class Renderer {
 public:
    virtual void render(const GameManager &gm) = 0;
};

#endif // RENDERER_H
