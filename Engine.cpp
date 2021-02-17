#include <SDL.h>
#include "Scene.h"
#include "Logger.h"
#include "Engine.h"

SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
Scene* Engine::currentScene = nullptr;
Scene* Engine::nextScene = nullptr;
bool Engine::runningFlag = false;

bool Engine::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::warn("Engine", "Failed to init SDL.");
		return false;
	}
	else {
		Logger::log("Engine", "Successfully initialized SDL.");
		return true;
	}
}

bool Engine::createWindow(std::string title, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	Engine::window = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
	if (Engine::window == nullptr) {
		Logger::warn("Engine", "Failed to create window.");
		return false;
	}

	Engine::renderer = SDL_CreateRenderer(Engine::window, 0, -1);
	if (Engine::renderer == nullptr) {
		Logger::warn("Engine", "Failed to create renderer.");
		return false;
	}

	return true;
}

void Engine::destroyWindow() {
	if (Engine::renderer != nullptr) {
		SDL_DestroyRenderer(Engine::renderer);
	}

	if (Engine::window != nullptr) {
		SDL_DestroyWindow(Engine::window);
	}
}

void Engine::unloadScene() {
	if (Engine::currentScene != nullptr) {
		delete Engine::currentScene;
		Engine::currentScene = nullptr;
	}
}

void Engine::run(unsigned int maxFps) {
	const auto interval = 1000 / maxFps;

	Engine::runningFlag = true;

	while (Engine::runningFlag) {
		auto start = SDL_GetTicks();

		if (Engine::nextScene != nullptr) {
			auto prev = Engine::currentScene;
			Engine::currentScene = Engine::nextScene;
			Engine::nextScene = nullptr;

			delete prev;
		}

		Engine::currentScene->refresh(Engine::renderer);

		auto end = SDL_GetTicks();

		if ((end - start) < interval) {
			SDL_Delay(interval - (end - start));
		}
	}
}

void Engine::stop() {
	Engine::runningFlag = false;
}

void Engine::quit() {
	Engine::unloadScene();

	if (Engine::renderer != nullptr) {
		SDL_DestroyRenderer(Engine::renderer);
		Engine::renderer = nullptr;
	}

	if (Engine::window != nullptr) {
		SDL_DestroyWindow(Engine::window);
		Engine::window = nullptr;
	}

	SDL_Quit();
}
