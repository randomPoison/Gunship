#pragma once

#include <cstddef>
#include <vector>
#include <limits>

class Scene;

typedef size_t component_id;

component_id GenerateUniqueComponentID();

class ComponentLocator
{
public:
	ComponentLocator( Scene* scene = nullptr, component_id id = 0, size_t index = 0 );

	Scene* scene;
	component_id id;
	size_t index;
};
