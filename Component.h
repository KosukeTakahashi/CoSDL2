#pragma once

#include <SDL.h>

class GameObject;
#include "GameObject.h"

class Component {
public:
	GameObject* parent;

	Component() : parent(nullptr) {}

	virtual void start() = 0;
	virtual void update() = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
};
