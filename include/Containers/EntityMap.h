#pragma once

#include "Entity/Entity.h"

namespace Gunship {
	namespace Containers {
		
		template < typename Element >
		class EntityMap
		{
		public:
			struct Bucket
			{
				Entity::ID entityID = 0;
				Element element;
			};

			EntityMap< Element >( size_t capacity = 7 )
				: _buckets( new Bucket[capacity] ),
				  _capacity( capacity ),
				  _count( 0 )
			{
			}

			~EntityMap< Element >()
			{
				delete[] _buckets;
			}

			void Put( Entity::ID entityID, Element element )
			{
				// TODO: Handle resizing the table.

				size_t index = Map( entityID );
				
				// Linear probing to find open bucket.
				while ( _buckets[index].entityID
				     && _buckets[index].entityID != entityID )
				{
					index = ( index + 1 ) % _capacity;
				}

				_buckets[index].entityID = entityID;
				_buckets[index].element = element;
			}

			Element& Get( Entity::ID entityID )
			{
				size_t index = Map( entityID );
				
				// Linear probing to find open bucket.
				while ( _buckets[index].entityID != entityID )
				{
					index = ( index + 1 ) % _capacity;
				}

				return _buckets[index].element;
			}

			void Remove( Entity::ID entityID )
			{
				size_t index = Map( entityID );
				
				// Linear probing to find open bucket.
				while ( _buckets[index].entityID != entityID )
				{
					index = ( index + 1 ) % _capacity;
				}

				// Zeroing-out the entity ID effectively removes the element.
				_buckets[index].entityID = 0;
			}

			bool Contains( Entity::ID entityID )
			{
				size_t index = Map( entityID );
				
				// Linear probing to find open bucket.
				while ( _buckets[index].entityID
				     && _buckets[index].entityID != entityID )
				{
					index = ( index + 1 ) % _capacity;
				}

				return _buckets[index].entityID == entityID;
			}

		private:
			Bucket* _buckets;
			size_t _capacity;
			size_t _count;

			size_t Map( Entity::ID entityID )
			{
				return Hash( entityID ) % _capacity;
			}

			size_t Hash( Entity::ID entityID )
			{
				return entityID;
			}
		};
	}
}
