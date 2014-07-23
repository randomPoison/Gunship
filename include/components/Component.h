#pragma once

#include <vector>

#include "GameObject.h"

// =====================================
// MACROS FOR USE IN CREATING COMPONENTS
// =====================================

#define COMPONENT_MEMBERS(componentName)	ComponentLocator< componentName > locator;\
											GameObject parent;

template< typename T >
struct ComponentLocator
{
	std::vector<T>* ComponentSet;
	int index;
};

// ==================================
// MACROS FOR USE IN USING COMPONENTS
// ==================================

#define DEFINE_COMPONENT(componentName) std::vector<componentName> __componentName__;
