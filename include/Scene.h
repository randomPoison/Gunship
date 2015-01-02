#pragma once

#include "Entity/SystemManager.h"
#include "Entity/EntityManager.h"

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
		explicit Scene( Engine* engine,
		                Ogre::Root* root,
		                Ogre::RenderWindow* renderWindow );

		template< typename S >
		void AddSystem()
		{
			_behaviorSystems.Add< S >();
		}
		Entity CreateGameObject();

		Engine& engine() const;
		Ogre::Root& ogreRoot() const;
		Ogre::RenderWindow& renderWindow() const;
		Ogre::SceneManager& sceneManager() const;
		EntityManager& entities();

	private:
		Engine* _engine;
		Ogre::Root* _root;
		Ogre::RenderWindow* _renderWindow;
		Ogre::SceneManager* _sceneManager;

		EntityManager _entities;
		SystemManager< DefaultSystemBase > _coreSystems;
		SystemManager< BehaviorSystemBase > _behaviorSystems;

		friend class Engine;

		/**
		 * @brief Update all the running systems.
		 *
		 * @details
		 *     This is called by the Engine as part of the normal frame loop,
		 *     and is not accessible to client code.
		 */
		void Update( float delta );
	};
}
