#pragma once

struct Component
{
	component_id id;

	Component();

	static component_id GenerateUniqueComponentID();
};

struct ComponentInfo
{
	component_id id;
	size_t index;
};

bool operator==( const Component& first, const Component& second );
