#pragma once

#include <vector>
#include <functional>

#include <v8.h>

#include <SDL_syswm.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <SDL_joystick.h>
#include <SDL_gamecontroller.h>
#include <SDL_assert.h>

#include <OgreRoot.h>
#include <OgreManualObject.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreVector3.h>

#include "Types.h"
#include "V8Helpers.h"
#include "Input.h"

#include "Components/Component.h"
#include "Components/GameObjectComponent.h"

#include "Scene.h"

/**
 * \brief A class representing an instance of the Gunship engine.
*/
class Gunship
{
public:
	// SDL variables
	SDL_Window* window;

	// Ogre variables
	Ogre::Root* root;
	Ogre::RenderWindow* renderWindow;

	// Gunship variables
	Scene* currentScene;
	Input input;

	// v8 variables
	v8::Isolate* isolate;
	v8::Persistent< v8::Context > _context;

	// default constructor
	Gunship();

	~Gunship();

	// initialization and shutdown functions
	bool InitSystems();
	bool InitializeV8();

	void Start();
	bool ShutDown();

	// other functions
	Scene* CurrentScene();
	Scene* ResetCurrentScene();
	Scene* ResetCurrentScene( std::function< void( Scene& ) > );

	/**
	 * \brief Loads and runs a startup script.
	 *
	 * \info A startup script is one that is used by Gunship to
	 * initialize the JS context.
	 */
	void RunStartupScript( const char* script );

	static std::string LoadScript( std::string script );
};

