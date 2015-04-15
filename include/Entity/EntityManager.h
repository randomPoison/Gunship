#pragma once

#include <deque>  ///< @todo Remove dependence on STL containers.
#include <unordered_set> ///< @todo Remove dependence on STL containers.

#include "Entity/Entity.h"

namespace Gunship
{
	class Scene;

	/// @brief Manager for creating and tracking live entities.
	class EntityManager
	{
	public:
		/// @brief Creates a new Entity with a unique ID.
		///
		/// @details
		///     Entity IDs are guaranteed to be unique among living
		///     entities. Entity IDs are recycled, so the entity may have
		///     the same ID as a previously created Entity, but only if
		///     that Entity has since been destroyed.
		///
		///     Entity IDs are generated linearly starting at 1. 0 is used
		///     as a sentinel value to mean "invalid entity", so no entity
		///     may ever have the ID of 0.
		Entity Create();

		/// @brief Destroys an existing Entity.
		///
		/// @details
		///     When an entity is destroyed its ID is reclaimed so that it
		///     may be used for the creation of future Entities. Reclaimed
		///     IDs are kept on a stack, so the last destroyed ID becomes
		///     the ID of the next created Entity.
		///
		///     Recovered IDs are stored in a queue to maximize the amount
		///     of time between when an entity is destroyed and when its ID
		///     is recycled. This is to give as much leeway as possible to
		///     detect if an entity has been destroyed.
		void Destroy( Entity::ID entityID );

		/// @brief Checks if the specified Entity is currently alive.
		///
		/// @details
		///     The lookup is done in constant time.
		bool Alive( Entity::ID entityID );

	private:
		static Entity::ID _idCounter;

		Scene& _scene;
		std::unordered_set< Entity::ID > _liveEntities;
		std::deque< Entity::ID > _freeIDs;

		friend class Scene;

		EntityManager( Scene& scene );
	};
}
