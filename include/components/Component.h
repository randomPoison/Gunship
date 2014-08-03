#pragma once

#include <cstddef>
#include <vector>
#include <limits>

class Scene;

typedef unsigned int component_id;
component_id GenerateUniqueComponentID();

template< typename T >
class ComponentLocator
{
public:
	ComponentLocator( Scene* scene = nullptr, component_id id = 0, size_t index = 0 ) :
		scene( scene ),
		id( id ),
		index( index )
	{
	}

private:
	Scene* scene;
	component_id id;
	size_t index;
};
