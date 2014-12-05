#pragma once

#include <vector>
#include <functional>

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
#include "Input.h"

#include "Scene.h"

namespace Gunship
{
	/**
	 * \brief A class representing an instance of the Gunship engine.
	 */
	class Engine
	{
	public:
		Engine();
		~Engine();

		/**
		 * \brief Initialize the engine's internal systems.
		 */
		bool InitSystems();

		/**
		 * \brief Run the engine's simulation.
		 */
		void Start();
		bool ShutDown();

		// other functions
		Scene* CurrentScene();
		Scene* ResetCurrentScene();

	private:
		// SDL variables
		SDL_Window* _window;

		// Ogre variables
		Ogre::Root* _root;
		Ogre::RenderWindow* _renderWindow;

		// Gunship variables
		Scene* _currentScene;
		Input _input;
	};
}
