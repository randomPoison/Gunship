#pragma once

#include <vector>
#include <functional>

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

		/**
		 * \brief Retrieve the current scene.
		 *
		 * \returns A pointer to the current scene.
		 */
		Gunship::Scene* CurrentScene();

	private:
		// SDL variables
		SDL_Window* _window;

		// Ogre variables
		Ogre::Root* _root;
		Ogre::RenderWindow* _renderWindow;

		// Gunship variables
		Gunship::Scene* _currentScene;
		Input _input;
	};
}
