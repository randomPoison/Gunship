#pragma once

#include <vector> // TODO Remove dependence on STL containers

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

	private:
		std::vector< ComponentType > _components;
	};

	struct SimpleStructComponent
	{
		Entity::ID entityID;
	};
}
