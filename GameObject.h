#pragma once

#include <string>
#include <optional>
#include <typeindex>
#include <unordered_map>
#include <exception>
#include <stdexcept>
#include <SDL.h>

class Scene;
#include "Scene.h"

class Component;
#include "Component.h"

class GameObject {
private:
	std::string label;
	std::unordered_map<std::type_index, Component*> components;

public:
	Scene* parent;

	GameObject(Scene* parent, std::string label);
	~GameObject();

	void start();
	void update();
	void render(SDL_Renderer* renderer);

	template <class T>
	T& addComponent() {
		static_assert(std::is_base_of<Component, T>::value);

		auto findResult = this->components.find(typeid(T));
		if (findResult != this->components.end()) {
			return *dynamic_cast<T*>(findResult->second);
		}
		else {
			auto component = new T();
			
			this->components.insert_or_assign(typeid(T), component);
			
			component->parent = this;
			component->start();
			
			return *component;
		}
	}

	template <class T>
	bool holdsComponent() const {
		static_assert(std::is_base_of<Component, T>::value);

		auto findResult = this->components.find(typeid(T));
		return findResult == this->components.end();
	}

	template <class T>
	T& getComponent() const {
		static_assert(std::is_base_of<Component, T>::value);

		auto findResult = this->components.find(typeid(T));
		if (findResult != this->components.end()) {
			return *dynamic_cast<T*>(findResult->second);
		}
		else {
			auto msg = std::string("This object holds no component of type ") + typeid(T).name();
			throw std::runtime_error(msg);
		}
	}

	template <class T>
	bool removeComponent() {
		static_assert(std::is_base_of<Component, T>::value);

		auto findResult = this->components.find(typeid(T));
		if (findResult != this->components.end()) {
			delete findResult->second;
			this->components.erase(findResult);
			return true;
		}
		else {
			return false;
		}
	}
};
