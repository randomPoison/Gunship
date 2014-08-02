#pragma once

#include <cstddef>
#include <vector>
#include <limits>

// forward declarations
class GameObject;

typedef unsigned int component_id;
component_id GenerateUniqueComponentID();

template< typename T >
class ComponentLocator
{
	std::vector<T>* componentSet;
	component_id id;
	size_t index;

public:
	ComponentLocator( std::vector<T>* set = nullptr, component_id id = 0, size_t index = std::numeric_limits< size_t >::max() ) :
		componentSet( set ),
		id( id ),
		index( index )
	{
	}

	T* GetComponent()
	{
		return componentSet->data() + index;
	}
};
