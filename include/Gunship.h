#pragma once

#include <vector>
#include <functional>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>

#include <OGRE/OgreVector3.h>

#include "Input.h"
#include "components/Component.h"
#include "components/CameraComponent.h"
#include "components/BehaviorComponent.h"
#include "GameObject.h"
#include "Scene.h"

// forward declarations because reasons
namespace Ogre {
	class Root;
	class RenderWindow;
};
struct SDL_Window;

class Gunship
{
public:
	// default constructor
	Gunship();

	~Gunship();

	// initialization and shutdown functions
	bool InitSystems();
	bool Configure();
	void Start();

	bool ShutDown();

	// other functions
	Scene* CurrentScene();
	Scene* ResetCurrentScene();
	Scene* ResetCurrentScene( std::function< void( Scene& ) > );

private:
	// Variables and stuffs
	SDL_Window* window;
	Ogre::Root* root;
	Ogre::RenderWindow* renderWindow;

	Scene* currentScene;
	Input input;
};
