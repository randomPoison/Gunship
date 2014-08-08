#pragma once

#include <functional>

class GameObject;

typedef std::function< void( GameObject&, const Input& ) > BehaviorFunction;

class BehaviorComponent
{
public:
	BehaviorComponent( GameObject& owner, BehaviorFunction function );

	BehaviorFunction behavior;

private:
	component_id id;
	component_id ownerId;

	friend class Scene;
};

class Behavior final : ComponentLocator
{
public:
	Behavior( Scene& scene, component_id id, size_t index = 0 );
};
