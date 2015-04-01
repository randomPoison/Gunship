#pragma once

#include <vector>        /// @todo Remove dependence on STL.
#include <unordered_map> /// @todo Remove dependence on STL.

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
	template < typename ComponentType >
	class SimpleStructComponentManager
	    : public ComponentManager< SimpleStructComponentManager< ComponentType > >
	{
	public:
		template < typename... Args >
		ComponentType& Assign( Entity::ID entityID, Args&&... args )
		{
			// Emplace new component into the components vector
			_components.emplace_back( std::forward< Args >( args )... );
			_components.back().entityID = entityID;

			// Associate its ID with its index
			_componentIndices[entityID] = _components.size() - 1;

			return _components.back();
		}

		/**
		 * @brief Retrieve a reference to the specified entity's component.
		 */
		ComponentType& Get( Entity::ID entityID )
		{
			SDL_assert_paranoid( _componentIndices.count( entityID ) );

			size_t index = _componentIndices[entityID];

			SDL_assert_paranoid( index < _components.size() );
			SDL_assert_paranoid( _components[index].entityID == entityID );

			return _components[index];
		}

		const std::vector< ComponentType >& components() const
		{
			return _components;
		}

	private:
		std::vector< ComponentType > _components;
		std::unordered_map< Entity::ID, size_t > _componentIndices;
	};
}
