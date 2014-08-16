#pragma once

#include <vector>
#include <functional>

#include <SDL_syswm.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <SDL_joystick.h>
#include <SDL_gamecontroller.h>

#include <OgreRoot.h>
#include <OgreManualObject.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreVector3.h>

#include "GunshipTypes.h"
#include "Input.h"
#include "components/Component.h"
#include "GameObject.h"
#include "components/CameraComponent.h"
#include "components/BehaviorComponent.h"
#include "Scene.h"

/**
 * \brief A class representing an instance of the Gunship engine.
*/
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
