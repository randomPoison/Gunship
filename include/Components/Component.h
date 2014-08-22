#pragma once

struct Component
{
	component_id id;
	GameObject owner;

	Component( GameObject& owner );

	static component_id GenerateUniqueComponentID();
};

bool operator==( const Component& first, const Component& second );
