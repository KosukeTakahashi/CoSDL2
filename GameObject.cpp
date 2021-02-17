#include <string>
#include <SDL.h>
#include "GameObject.h"

class Scene;
#include "Scene.h"

GameObject::GameObject(Scene* parent, std::string label) : parent(parent), label(label) {}

GameObject::~GameObject() {
	for (auto& [_, component] : this->components) {
		delete component;
	}
	this->components.clear();
}

void GameObject::start() {
	for (auto& [_, component] : this->components) {
		component->start();
	}
}

void GameObject::update() {
	for (auto& [_, component] : this->components) {
		component->update();
	}
}

void GameObject::render(SDL_Renderer* renderer) {
	for (auto& [_, component] : this->components) {
		component->render(renderer);
	}
}
