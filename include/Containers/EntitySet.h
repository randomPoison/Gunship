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

			void Put( Entity entity );
			void Remove( Entity entity );
			bool Contains( Entity entity );

		private:
			Entity* _buckets;
			size_t _capacity;
			size_t _count;
			size_t _itemsUntilRehash;

			size_t Map( Entity entity );
			size_t Hash( Entity entity );

			void Rehash();

			static Entity* Allocate( size_t capacity );
		};
	}
}
