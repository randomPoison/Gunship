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

		void EntitySet::Put( Entity entity )
		{
			// Linear probing to find open bucket.
			size_t index = Map( entity );
			while ( _buckets[index]
			     && _buckets[index] != entity )
			{
				index = ( index + 1 ) % _capacity;
			}

			// If we're not overwriting an existing value, increase
			// the count and decrease items until rehash.
			if ( _buckets[index] != entity )
			{
				_count += 1;
				_itemsUntilRehash -= 1;
			}

			_buckets[index] = entity;

			// If no more items until rehash perform the rehash.
			if ( _itemsUntilRehash == 0 )
			{
				Rehash();
			}
		}

		void EntitySet::Remove( Entity entity )
		{
			// Linear probing to find open bucket.
			size_t index = Map( entity );
			while ( _buckets[index] != entity )
			{
				index = ( index + 1 ) % _capacity;
			}

			// Zeroing-out the entity ID effectively removes the element.
			_buckets[index].id = 0;

			// Adjust count and items until rehash.
			_count -= 1;
			_itemsUntilRehash += 1;
		}

		bool EntitySet::Contains( Entity entity )
		{
			size_t index = Map( entity );

			// Linear probing to find open bucket.
			while ( _buckets[index]
			      && _buckets[index] != entity )
			{
				index = ( index + 1 ) % _capacity;
			}

			return _buckets[index] == entity;
		}

		size_t EntitySet::Map( Entity entity )
		{
			return Hash( entity ) % _capacity;
		}

		size_t EntitySet::Hash( Entity entity )
		{
			return entity;
		}

		void EntitySet::Rehash()
		{
			// Update capacity and buckets, temporarily caching off the
			// old values so that we can transfer the elements.
			size_t oldCapacity = _capacity;
			_capacity *= 2;

			Entity* oldBuckets = _buckets;
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

		Entity* EntitySet::Allocate( size_t capacity )
		{
			void* rawBytes = std::calloc( capacity, sizeof( Entity ) );
			return static_cast< Entity* >( rawBytes );
		}
	}
}
