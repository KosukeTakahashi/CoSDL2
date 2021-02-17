#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <SDL.h>

class GameObject;
#include "GameObject.h"

class Scene {
protected:
	std::unordered_map<std::string, GameObject*> objects;

public:
	Scene();
	~Scene();

	void refresh(SDL_Renderer* renderer);
	GameObject& addGameObject(std::string label);
	bool holdsGameObject(std::string label) const;
	GameObject& getGameObject(std::string label) const;
	bool removeGameObject(std::string label);
};
