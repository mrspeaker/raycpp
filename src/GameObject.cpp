#include "GameObject.h"

GameObject::GameObject(): active(true) {
	pos.x = 0;
	pos.y = 0;
	vel.x = 0;
    vel.y = 0;
};

GameObject::GameObject(float x, float y): active(true) {
	pos.x = x;
	pos.y = y;
	vel.x = 0;
    vel.y = 0;
};

void GameObject::destroy() {
	active = false;
};

void GameObject::update() {
	pos.x += vel.x;
    pos.y += vel.y;
};

void GameObject::set_pos(float x, float y) {
	pos.x = x;
	pos.y = y;
	vel.x = 0.0f;
    vel.y = 0.0f;
};
