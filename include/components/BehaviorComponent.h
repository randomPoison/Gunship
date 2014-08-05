#pragma once

#include <functional>

class GameObject;

typedef std::function< void( GameObject& ) > BehaviorFunction;

class BehaviorComponent
{
public:
	BehaviorComponent( BehaviorFunction function );

	BehaviorFunction behavior;

private:
	component_id id;

	friend class Scene;
};

class Behavior final : ComponentLocator
{
public:
	Behavior( Scene& scene, component_id id, size_t index = 0 );
};
