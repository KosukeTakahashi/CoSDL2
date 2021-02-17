#include "Scene.h"
#include <SDL.h>
#include <optional>
#include <string>
#include <exception>
#include <stdexcept>
#include "GameObject.h"

Scene::Scene() {}

Scene::~Scene() {
	for (auto& [_, object] : this->objects) {
		delete object;
	}
	this->objects.clear();
}

void Scene::refresh(SDL_Renderer* renderer) {
	for (auto& [_, object] : this->objects) {
		object->update();
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	for (auto& [_, object] : this->objects) {
		object->render(renderer);
	}

	SDL_RenderPresent(renderer);
}

GameObject& Scene::addGameObject(std::string label) {
	auto findResult = this->objects.find(label);
	if (findResult != this->objects.end()) {
		return *(findResult->second);
	}

	auto obj = new GameObject(this, label);
	this->objects.insert(std::make_pair(label, obj));

	obj->parent = this;
	obj->start();

	return *obj;
}

bool Scene::holdsGameObject(std::string label) const {
	auto findResult = this->objects.find(label);
	return findResult != this->objects.end();
}

GameObject& Scene::getGameObject(
	std::string label) const {
	auto findResult = this->objects.find(label);
	if (findResult != this->objects.end()) {
		return *(findResult->second);
	}
	else {
		auto msg = "This Scene holds no GameObject whose label is " + label;
		throw std::runtime_error(msg);
	}
}

bool Scene::removeGameObject(std::string label) {
	auto findResult = this->objects.find(label);
	if (findResult != this->objects.end()) {
		auto obj = findResult->second;
		delete obj;

		this->objects.erase(findResult);

		return true;
	}
	else {
		return false;
	}
}
