#pragma once

#include "Entity/Entity.h"

namespace Gunship
{
	namespace Containers
	{
		class EntitySet
		{
		public:
			EntitySet( size_t capactiy = 7 );
			~EntitySet();

			void Put( Entity::ID entityID );
			void Remove( Entity::ID entityID );
			bool Contains( Entity::ID entityID );

		private:
			Entity::ID* _buckets;
			size_t _capacity;
			size_t _count;

			size_t Map( Entity::ID entityID );
			size_t Hash( Entity::ID entityID );
		};
	}
}
