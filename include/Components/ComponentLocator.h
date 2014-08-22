#pragma once

class Scene;

class ComponentLocator
{
public:
	ComponentLocator( Scene* scene = nullptr, component_id id = 0, size_t index = 0 );
	
	virtual void Destroy() = 0;

	Scene* scene;
	component_id id;
	size_t index;
};

bool operator==( const ComponentLocator& first, const ComponentLocator& second );
