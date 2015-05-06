#pragma once

#include <SDL_assert.h>

#include "Entity/Entity.h"
#include "Entity/ComponentManager.h"
#include "Containers/EntityMap.h"
#include "Containers/FastArray.h"

namespace Gunship
{
	/// @brief A default component manager for easily creating stuct components.
	///
	/// @details
	///     Most gameplay components are likely to just be structs with the
	///     necessary data, so to simplify development the SimpleStructComponentManager
	///     is provided to make it possible to define new components of this
	///     type without having to create a new ComponentManager.
	template < typename ComponentType >
	class SimpleStructComponentManager
		: public ComponentManager< SimpleStructComponentManager< ComponentType > >
	{
	public:
		SimpleStructComponentManager< ComponentType >()
		{
		}

		/// @brief Assigns one component to the entity, constructing it with arguments provided.
		///
		/// @note
		///     This is meant to be a utility method provided to children of this class,
		///     who should provide their own interface for assigning components
		///     which only takes the necessary arguments.
		///
		///     For example, if the component type requires the scene to be passed in
		///     to the constructor, then the manager should cache off a reference to the
		///     scene on construction and automatically pass the scene to new components
		///     so that clients do not have to remember to do so every time.
		template < typename... Args >
		ComponentType& Assign( Entity::ID entityID, Args&&... args )
		{
			SDL_assert_paranoid( !_indices.Contains( entityID ) );

			// Emplace new component into the components vector
			auto& element = _components.Push( ComponentType( std::forward< Args >( args )... ) );
			element.entityID = entityID;

			// Associate its ID with its index
			_indices.Put( entityID, _components.count() - 1 );

			return element;
		}

		/// @brief Marks the entity's associated component for destruction.
		///
		/// @note
		///     This only marks the component for deferred destruction,
		///     and will continue to exist and be accessible until the end
		///     of the frame. At the end of each frame Gunship destroys all
		///     marked components.
		///
		///     This method will assert in debug builds if the entity does not
		///     have an associated component.
		void Destroy( Entity::ID entityID )
		{
			_markedForDestruction.Push( entityID );
		}

		void DestroyAll( Entity::ID entityID ) override
		{
			if ( _indices.Contains( entityID ) )
			{
				Destroy( entityID );
			}
		}

		void DestroyAllMarked() override
		{
			for ( Entity::ID entityID : _markedForDestruction )
			{
				// We have to check first if the component exists.
				// We check when marking the component for destruction
				// that the component exists, but we don't check if its
				// already been marked, so if it doesn't exist here we
				// can assume that it was marked twice and has already
				// beend destroyed.
				if ( _indices.Contains( entityID ) )
				{
					DestroyImmediate( entityID );
				}
			}

			_markedForDestruction.Clear();
		}

		/// @brief Retrieve a reference to the specified entity's component.
		ComponentType& Get( Entity::ID entityID )
		{
			SDL_assert_paranoid( _indices.Contains( entityID ) );

			size_t index = _indices.Get( entityID );

			SDL_assert_paranoid( index < _components.count() );
			SDL_assert_paranoid( _components[index].entityID == entityID );

			return _components[index];
		}

		const Containers::FastArray< ComponentType >& components() const
		{
			return _components;
		}

	private:
		Containers::FastArray< ComponentType > _components;
		Containers::EntityMap< size_t > _indices;

		Containers::FastArray< Entity::ID > _markedForDestruction;

		/// @brief Destroys the component associated with the given Entity.
		///
		/// @details
		///     Destruction occurs in constant time, and does not require
		///     the elements of the internal array to be shifted, so only
		///     the destroyed component and the last component in the
		///     array are affected.
		void DestroyImmediate( Entity::ID entityID )
		{
			// Retrieve the index of the component to be destroyed, then
			// remove the component to be destroyed from the index map.
			size_t index = _indices.Get( entityID );
			_indices.Remove( entityID );

			// If the component isn't at the end of the vector,
			// swap the last component into the destroyed component's spot.
			// Otherwise we can just pop the end of the vector.
			if ( index != _components.count() - 1 )
			{
				// Swap the positions of the two components
				std::swap( _components[index], _components.Peek() );

				// Put the moved component's index back in the map.
				_indices.Put( _components[index].entityID, index );
			}

			// The marked component is now guaranteed to be at the end.
			// Pop the last element to destroy it.
			_components.Pop();
		}
	};
}
