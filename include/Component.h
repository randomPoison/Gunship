#pragma once

#include <vector>

#define COMPONENT_MEMBERS(componentName)	int index;\
											void Update();

#define DEFINE_COMPONENT(componentName) std::vector<componentName> __componentName__;

#define ADD_COMPONENT(componentName)

#define INITIALIZE_COMPONENT(componentName)

#define DESTROY_COMPONENT(componentName)

template< typename T >
struct ComponentLocator
{
	std::vector<T>* ComponentSet;
	int index;
};
