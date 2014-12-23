#pragma once

#include <OgreRoot.h>
#include <OgreRenderWindow.h>

#include "Types.h"
#include "Input.h"

namespace Gunship
{
	class Scene;

	typedef void ( *SceneInitFunction )( Scene& );

	/**
	 * @brief A class representing an instance of the Gunship engine.
	 */
	class Engine
	{
	public:
		explicit Engine();
		~Engine();

		/**
		 * @brief Initialize the engine's internal systems.
		 */
		bool InitSystems();

		/**
		 * @brief Throws away the current scene (if one exists) and creates a new one.
		 *
		 * @param initializationFunction
		 *     A function which, given the new scene, will construct
		 *     the scene's initial state.
		 */
		void SetupCurrentScene( SceneInitFunction initializationFunction );

		/**
		 * @brief Run the engine's simulation.
		 *
		 * @note
		 *     This method contains the main game loop, and will block
		 *     until the engine is told to shut down.
		 */
		void Start();

		/**
		 * @brief Shut down the engine and its subsystems.
		 */
		bool ShutDown();

		/**
		 * @brief Retrieve the current scene.
		 *
		 * @returns
		 *     A pointer to the current scene.
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
	};
}
