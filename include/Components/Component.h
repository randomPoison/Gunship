#pragma once

struct Component
{
	GameObject owner;
	component_id id;

	Component( GameObject& owner );

	static component_id GenerateUniqueComponentID();
};

bool operator==( const Component& first, const Component& second );
