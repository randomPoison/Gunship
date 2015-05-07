#pragma once

#include <SDL_assert.h>

#include "Entity/Entity.h"
#include "Entity/ComponentManager.h"
#include "Containers/EntityMap.h"
#include "Containers/FastArray.h"

namespace Gunship
{
	/// @brief A pooled version of SimpleStructComponentManager.
	///
	/// @details
	///     Provides similar functionality to SimpleStructComponentManager,
	///     but pools destroyed resources without destructing them and reuses
	///     them when a new component is needed. This is useful for simple
	///     components that are costly to create and destroy, or when components
	///     hold resources that can be reused rather than destroyed.
	template < typename ComponentType >
	class PooledComponentManager
		: public ComponentManager< PooledComponentManager< ComponentType > >
	{
	public:
		PooledComponentManager< ComponentType >()
		{
		}

		/// @brief Assigns one component to the entity, constructing or enabling it with arguments provided.
		///
		/// @details
		///     This is meant to be a utility method provided to children of this class,
		///     who should provide their own interface for assigning components
		///     which only takes the necessary arguments.
		///
		///     For example, if the component type requires the scene to be passed in
		///     to the constructor, then the manager should cache off a reference to the
		///     scene on construction and automatically pass the scene to new components
		///     so that clients do not have to remember to do so every time.
		///
		///     If there are components left in the pool then the first one will be reused
		///     rather than creating a new component. Enable() will still be called in this case.
		template < typename... Args >
		ComponentType& Assign( Entity entity )
		{
			SDL_assert_paranoid( !_indices.Contains( entity ) );

			// If there are no pooled components create a new one.
			if ( _liveCount == _components.count() )
			{
				_components.Push( Construct( entity ) );
			}

			// Assign the first pooled component with the entity and enable it.
			++_liveCount;
			ComponentType& component = _components.Peek();
			component.entity = entity;
			Enable( entity, component );

			// Add its index to the index map.
			_indices.Put( entity, _liveCount - 1 );

			return component;
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
		void Destroy( Entity entity )
		{
			_markedForDestruction.Push( entity );
		}

		void DestroyAll( Entity entity ) override
		{
			Destroy( entity );
		}

		void DestroyAllMarked() override
		{
			for ( Entity entity : _markedForDestruction )
			{
				// We have to check first if the component exists.
				// We check when marking the component for destruction
				// that the component exists, but we don't check if its
				// already been marked, so if it doesn't exist here we
				// can assume that it was marked twice and has already
				// beend destroyed.
				if ( _indices.Contains( entity ) )
				{
					DestroyImmediate( entity );
				}
			}

			_markedForDestruction.Clear();
		}

		/// @brief Retrieve a reference to the specified entity's component.
		ComponentType& Get( Entity entity )
		{

			SDL_assert_paranoid( _indices.Contains( entity ) );

			size_t index = _indices.Get( entity );

			SDL_assert_paranoid( index < _components.count() );
			SDL_assert_paranoid( _components[index].entity == entity );

			return _components[index];
		}

		const Containers::FastArray< ComponentType >& components() const
		{
			return _components;
		}

		/// @brief Called when a component is destroyed and returned to the pool.
		///
		/// @details
		///     This method should perform any necessary actions to disable the
		///     component when it is no longer being used.
		virtual void Disable( ComponentType& component ) = 0;

		/// @brief Called when a component is being assigned to an entity.
		///
		/// @details
		///     This method should perform any necessary actions to initialize the
		///     component before use. It is called every time the component is assigned
		///     to an entity, including when the component is first created.
		virtual void Enable( Entity entity, ComponentType& component ) = 0;

		virtual ComponentType Construct( Entity entity ) = 0;
		virtual void Destruct( ComponentType& component ) = 0;

	private:
		Containers::FastArray< ComponentType > _components;
		size_t _liveCount = 0;
		Containers::EntityMap< size_t > _indices;

		Containers::FastArray< Entity > _markedForDestruction;

		/// @brief Returns the component associated with the given Entity back to the pool.
		///
		/// @details
		///     Destruction occurs in constant time, and does not require
		///     the elements of the internal array to be shifted, so only
		///     the destroyed component and the last component in the
		///     array are affected.
		///
		/// @note
		///     The destroyed component is not destructed and remains in the
		///     list of components. When an
		void DestroyImmediate( Entity entity )
		{
			// Retrieve the index of the component to be destroyed, then
			// remove it from the index map.
			size_t index = _indices.Get( entity );
			_indices.Remove( entity );

			// Make sure we actually have the right index, EntityMap is still a WIP.
			SDL_assert_paranoid( _components[index].entity == entity );

			// If the component isn't the last live one, swap the
			// last live component into the destroyed component's spot.
			// Otherwise we can just pop the end of the vector.
			if ( index != _liveCount - 1 )
			{
				// Swap the positions of the two components
				std::swap( _components[index], _components[_liveCount - 1] );

				// Put the moved component's index back in the map.
				_indices.Put( _components[index].entity, index );
			}

			// Decrease the live count, effectively marking the
			// component as destroyed.
			--_liveCount;

			// Do the callback to disable the component.
			Disable( _components[_liveCount] );

			SDL_assert_paranoid( !_indices.Contains( entity ) );
		}
	};
}
