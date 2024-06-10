#pragma once

#include <raylib-cpp.hpp>

class GameObject {
 private:
 public:
    bool active;
    Vector2 pos;
    Vector2 vel;

    GameObject();
    GameObject(float x, float y);
    virtual ~GameObject() = default;

    void destroy();
    virtual void update();
    void set_pos(float x, float y);
};
