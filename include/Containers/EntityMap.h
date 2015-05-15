#pragma once

#include <cstdlib>

#include "Entity/Entity.h"

namespace Gunship {
	namespace Containers {
		
		template < typename Element >
		class EntityMap
		{
		public:
			struct Bucket
			{
				Entity entity;
				Element element;
			};

			EntityMap< Element >( size_t capacity = 7 )
				: _buckets( Allocate( capacity ) ),
				  _capacity( capacity ),
				  _count( 0 ),
				  _itemsUntilRehash( ( capacity * 3 ) / 4 )
			{
			}

			~EntityMap< Element >()
			{
				std::free( _buckets );
			}

			void Put( Entity entity, Element element )
			{
				// Linear probing to find open bucket.
				size_t index = Map( entity );
				while ( _buckets[index].entity
				     && _buckets[index].entity != entity )
				{
					index = ( index + 1 ) % _capacity;
				}

				// If we're not overwriting an existing value, increase
				// the count and decrease items until rehash.
				if ( _buckets[index].entity != entity )
				{
					_count += 1;
					_itemsUntilRehash -= 1;
				}

				_buckets[index].entity = entity;
				_buckets[index].element = element;

				// If no more items until rehash perform the rehash.
				if ( _itemsUntilRehash == 0 )
				{
					Rehash();
				}
			}

			Element& Get( Entity entity )
			{
				size_t index = Map( entity );
				
				// Linear probing to find open bucket.
				while ( _buckets[index].entity != entity )
				{
					index = ( index + 1 ) % _capacity;
				}

				return _buckets[index].element;
			}

			void Remove( Entity entity )
			{
				// Linear probing to find open bucket.
				size_t index = Map( entity );
				while ( _buckets[index].entity != entity )
				{
					index = ( index + 1 ) % _capacity;
				}

				// Zeroing-out the entity ID effectively removes the element.
				_buckets[index].entity.id = 0;

				// Adjust count and items until rehash.
				_count -= 1;
				_itemsUntilRehash += 1;
			}

			bool Contains( Entity entity )
			{
				size_t index = Map( entity );
				
				// Linear probing to find open bucket.
				while ( _buckets[index].entity
				     && _buckets[index].entity != entity )
				{
					index = ( index + 1 ) % _capacity;
				}

				return _buckets[index].entity == entity;
			}

		private:
			Bucket* _buckets;
			size_t _capacity;
			size_t _count;
			size_t _itemsUntilRehash;

			size_t Map( Entity::ID entityID )
			{
				return Hash( entityID ) % _capacity;
			}

			size_t Hash( Entity::ID entityID )
			{
				return entityID;
			}

			/// @brief Reallocates the underlying table and rehashes the existing elements into it.
			///
			/// @details
			///     The new table is double the size of the old table. To transfer the old elements
			///     to the new table, the old buckets are iterated over and the ones with contents
			///     are re-hashed into the new table.
			void Rehash()
			{
				// Update capacity and buckets, temporarily caching off the
				// old values so that we can transfer the elements.
				size_t oldCapacity = _capacity;
				_capacity *= 2;

				Bucket* oldBuckets = _buckets;
				_buckets = Allocate( _capacity );

				// Reset count and elements until rehash so that
				// Put() can update them accordingly.
				_count = 0;
				_itemsUntilRehash = ( _capacity * 3 ) / 4;

				// Transfer the existing elements into the new table.
				for ( size_t index = 0; index < oldCapacity; ++index )
				{
					if ( oldBuckets[index].entity )
					{
						Put( oldBuckets[index].entity, oldBuckets[index].element );
					}
				}

				// Free the old table.
				std::free( oldBuckets );
			}

			/// @brief Allocates the underlying table and fills it with 0s.
			///
			/// @remarks
			///     0 is used as a sentinel value to indicate that the bucket is
			///     unused, so we manually allocate the raw bytes for the table
			///     and initialize 0s into them to avoid having to perform /a capacity
			///     calls to the Bucket constructor to initialize those values.
			static Bucket* Allocate( size_t capacity )
			{
				void* rawBytes = std::calloc( capacity, sizeof( Bucket ) );
				return static_cast< Bucket* >( rawBytes );
			}
		};
	}
}
