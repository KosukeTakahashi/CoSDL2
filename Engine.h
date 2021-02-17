#pragma once

#include <string>
#include <SDL.h>
#include "Scene.h"

class Engine {
private:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static Scene* currentScene;
	static Scene* nextScene;
	static bool runningFlag;

public:
	static bool init();

	static bool createWindow(std::string title, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

	static void destroyWindow();

	static void unloadScene();

	static void run(unsigned int maxFps);

	static void stop();

	static void quit();

	template <class T>
	static void loadScene() {
		static_assert(std::is_base_of<Scene, T>::value);

		if (Engine::nextScene != nullptr) {
			delete Engine::nextScene;
		}

		Engine::nextScene = new T();
	}
};
