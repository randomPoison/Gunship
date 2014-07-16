#pragma once

#include <vector>

#define COMPONENT_MEMBERS(componentName)	int index;\
											void update();

#define ADD_COMPONENT(componentName)

#define INITIALIZE_COMPONENT(componentName)

#define DESTROY_COMPONENT(componentName)

template< typename T >
struct ComponentLocator
{
	std::vector<T>* ComponentSet;
	int index;
};
