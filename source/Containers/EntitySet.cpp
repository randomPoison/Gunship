#include <cstdlib>

#include "Containers/EntitySet.h"

namespace Gunship
{
	namespace Containers
	{
		EntitySet::EntitySet( size_t capactiy )
			: _buckets( Allocate( capactiy ) ),
			  _capacity( capactiy ),
			  _count( 0 ),
			  _itemsUntilRehash( capactiy * 3 / 4 )
		{
		}

		EntitySet::~EntitySet()
		{
			delete[] _buckets;
		}

		void EntitySet::Put( Entity::ID entityID )
		{
			// Linear probing to find open bucket.
			size_t index = Map( entityID );
			while ( _buckets[index]
			     && _buckets[index] != entityID )
			{
				index = ( index + 1 ) % _capacity;
			}

			// If we're not overwriting an existing value, increase
			// the count and decrease items until rehash.
			if ( _buckets[index] != entityID )
			{
				_count += 1;
				_itemsUntilRehash -= 1;
			}

			_buckets[index] = entityID;

			// If no more items until rehash perform the rehash.
			if ( _itemsUntilRehash == 0 )
			{
				Rehash();
			}
		}

		void EntitySet::Remove( Entity::ID entityID )
		{
			// Linear probing to find open bucket.
			size_t index = Map( entityID );
			while ( _buckets[index] != entityID )
			{
				index = ( index + 1 ) % _capacity;
			}

			// Zeroing-out the entity ID effectively removes the element.
			_buckets[index] = 0;

			// Adjust count and items until rehash.
			_count -= 1;
			_itemsUntilRehash += 1;
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

		void EntitySet::Rehash()
		{
			// Update capacity and buckets, temporarily caching off the
			// old values so that we can transfer the elements.
			size_t oldCapacity = _capacity;
			_capacity *= 2;

			Entity::ID* oldBuckets = _buckets;
			_buckets = Allocate( _capacity );

			// Reset count and elements until rehash so that
			// Put() can update them accordingly.
			_count = 0;
			_itemsUntilRehash = ( _capacity * 3 ) / 4;

			// Transfer the existing elements into the new table.
			for ( size_t index = 0; index < oldCapacity; ++index )
			{
				if ( oldBuckets[index] )
				{
					Put( oldBuckets[index] );
				}
			}

			// Free the old table.
			std::free( oldBuckets );
		}

		Entity::ID* EntitySet::Allocate( size_t capacity )
		{
			void* rawBytes = std::calloc( capacity, sizeof( Entity::ID ) );
			return static_cast< Entity::ID* >( rawBytes );
		}
	}
}
