#pragma once

#include <unordered_map> ///< @todo remove STL dependency
#include <memory.h>      ///< @todo remove STL dependency

#include "Entity/SystemManager.h"
#include "Entity/EntityManager.h"
#include "Entity/ComponentManager.h"

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

		template< typename ComponentManager >
		void RegisterComponentManager( ComponentManager* componentManager )
		{
			_componentManagers[ComponentManager::id()] = std::shared_ptr< ComponentManagerBase >( componentManager );
		}

		template< typename ComponentManager >
		ComponentManager& componentManager()
		{
			return static_cast< ComponentManager& >( _componentManager( ComponentManager::id() ) );
		}

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

		std::unordered_map< ComponentManagerBase::ID, std::shared_ptr< ComponentManagerBase > > _componentManagers;

		friend class Engine;

		/**
		 * @brief Update all the running systems.
		 *
		 * @details
		 *     This is called by the Engine as part of the normal frame loop,
		 *     and is not accessible to client code.
		 */
		void Update( float delta );

		ComponentManagerBase& _componentManager( ComponentManagerBase::ID id );
	};
}
