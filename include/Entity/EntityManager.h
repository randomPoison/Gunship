#pragma once

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
		void Destroy();

		bool Alive( Entity entity );
		bool Alive( Entity::ID entityID );

	private:
		static Entity::ID _idCounter;
	};
}
