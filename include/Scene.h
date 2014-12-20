#pragma once

#include <entityx/Entity.h>
#include <entityx/Event.h>
#include <entityx/System.h>

#include "Input.h"

namespace Ogre
{
	class Root;
	class RenderWindow;
	class SceneManager;
}

namespace Gunship
{
	class Engine;

	class Scene
	{
	public:
		explicit Scene( Engine* engine, Ogre::Root* root,
		    Ogre::RenderWindow* renderWindow );

		template< typename S >
		void AddSystem()
		{
			_behaviorSystems.add< S >();
		}
		entityx::Entity CreateGameObject();

		Engine& engine() const;
		Ogre::Root& ogreRoot() const;
		Ogre::RenderWindow& renderWindow() const;
		Ogre::SceneManager& sceneManager() const;

	private:
		Engine* _engine;
		Ogre::Root* _root;
		Ogre::RenderWindow* _renderWindow;
		Ogre::SceneManager* _sceneManager;

		entityx::EventManager _events;
		entityx::EntityManager _entities;
		entityx::SystemManager _coreSystems;
		entityx::SystemManager _behaviorSystems;

		friend class Engine;

		/**
		 * \brief Update all the running systems.
		 */
		void Update( float delta );
	};
}
