#pragma once

#include <vector> /// @todo Remove dependence on STL containers
#include <utility>
#include <algorithm>

#include <SDL_assert.h>

#include "Entity/Entity.h"
#include "Entity/ComponentManager.h"

namespace Gunship
{
	/**
	 * @brief A default component manager for easily creating stuct components.
	 *
	 * @details
	 *     Most gameplay components are likely to just be structs with the
	 *     necessary data, so to simplify development the SimpleStructComponentManager
	 *     is provided to make it possible to define new components of this
	 *     type without having to create a new ComponentManager.
	 */
	template< typename ComponentType >
	class SimpleStructComponentManager
		: public ComponentManager< SimpleStructComponentManager< ComponentType > >
	{
	public:
		template< typename ... Args >
		ComponentType& Assign( Entity::ID entity, Args&& ... args )
		{
			_components.emplace_back( std::forward< Args >( args ) ... );
			_components.back().entityID = entity;
			return _components.back();
		}

		/**
		 * @brief Retrieve a reference to the specified entity's component.
		 */
		ComponentType& Get( Entity::ID entity )
		{
			auto iterator = std::find_if( _components.begin(), _components.end(),
				[ = ]( ComponentType& component )
				{
					return component.entityID == entity;
				} );

			SDL_assert_paranoid( iterator != _components.end() );

			return *iterator;
		}

		const std::vector< ComponentType >& components() const
		{
			return _components;
		}

	private:
		std::vector< ComponentType > _components;
	};
}
