#pragma once

#include <deque>
#include <vector>

#include "Entity/Entity.h"

namespace Gunship
{
	/**
	 * @brief Manager for creating and tracking live entities.
	 */
	class EntityManager
	{
	public:
		Entity Create();
		void Destroy( Entity entity );
		void Destroy( Entity::ID entityID );

		bool Alive( Entity entity );
		bool Alive( Entity::ID entityID );

	private:
		static Entity::ID _idCounter;

		std::vector< Entity::ID > _liveEntities; // TODO make this something more appropriate than a flat list
		std::deque< Entity::ID > _freeIDs;       // TODO make this something more appropraite than a flat list
	};
}
