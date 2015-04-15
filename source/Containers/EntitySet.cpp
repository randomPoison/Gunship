#include <cstring>

#include "Containers/EntitySet.h"

namespace Gunship
{
	namespace Containers
	{
		EntitySet::EntitySet( size_t capactiy )
			: _buckets( new Entity::ID[capactiy] ),
			  _capacity( capactiy ),
			  _count( 0 )
		{
			// Initialize all entity IDs to 0, which signals there is no entity.
			std::memset( _buckets, 0, sizeof( _buckets[0] ) * _capacity );
		}

		EntitySet::~EntitySet()
		{
			delete[] _buckets;
		}

		void EntitySet::Put( Entity::ID entityID )
		{
			// TODO: Handle resizing the table.

			size_t index = Map( entityID );

			// Linear probing to find open bucket.
			while ( _buckets[index]
			     && _buckets[index] != entityID )
			{
				index = ( index + 1 ) % _capacity;
			}

			_buckets[index] = entityID;
		}

		void EntitySet::Remove( Entity::ID entityID )
		{
			size_t index = Map( entityID );

			// Linear probing to find open bucket.
			while ( _buckets[index] != entityID )
			{
				index = ( index + 1 ) % _capacity;
			}

			// Zeroing-out the entity ID effectively removes the element.
			_buckets[index] = 0;
		}

		bool EntitySet::Contains( Entity::ID entityID )
		{
			size_t index = Map( entityID );

			// Linear probing to find open bucket.
			while ( _buckets[index]
			      && _buckets[index] != entityID )
			{
				index = ( index + 1 ) % _capacity;
			}

			return _buckets[index] == entityID;
		}

		size_t EntitySet::Map( Entity::ID entityID )
		{
			return Hash( entityID ) % _capacity;
		}

		size_t EntitySet::Hash( Entity::ID entityID )
		{
			return entityID;
		}
	}
}
