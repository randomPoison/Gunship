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

		/// @brief Register the provided ComponentManager object with the scene.
		///
		/// @details
		///     The ComponentManager object provided must inherit from ComponentManagerBase.
		///
		/// @todo
		///     As per essential c++'s recommendation, change this method to take a
		///     std::shared_ptr rather than a raw pointer for the sake of exception safety.
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
		friend class EntityManager;

		/// @brief Update all the running systems.
		///
		/// @details
		///     This is called by the Engine as part of the normal frame loop,
		///     and is not accessible to client code.
		void Update( float delta );

		/// @brief Retries a reference to the ComponentManagerBase with the specified ID.
		///
		/// @details
		///     To reduce the cost of recompiling generic code this provides the bulk
		///     of the work to retrive a reference to a component manager. The
		///     templated version simply provides a wrapper that automatically
		///     retrieves the ID and typecasts the result.
		ComponentManagerBase& _componentManager( ComponentManagerBase::ID id );
	};
}
