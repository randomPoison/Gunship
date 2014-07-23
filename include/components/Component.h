#pragma once

#include <vector>

// forward declarations
class GameObject;

// MACROS

#define COMPONENT_MEMBERS(componentName)	ComponentLocator< componentName > locator;\
											ComponentLocator< GameObject > owner;

// HELPERS

template< typename T >
struct ComponentLocator
{
	std::vector<T>* componentSet;
	int index;

	ComponentLocator( std::vector<T>* set = nullptr, int index = -1) : componentSet(set), index(index) { }
};
