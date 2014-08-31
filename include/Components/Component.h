#pragma once

struct Component
{
	component_id id;

	Component();

	static component_id GenerateUniqueComponentID();
};

bool operator==( const Component& first, const Component& second );
