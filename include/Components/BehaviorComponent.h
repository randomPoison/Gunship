#pragma once

#include <functional>

class GameObject;

class BehaviorComponent
{
public:
	BehaviorComponent( GameObject& owner, BehaviorFunction function );

	BehaviorFunction behavior;

private:
	component_id id;
	GameObject owner;

	friend class Scene;
};

class Behavior final : public ComponentLocator
{
public:
	Behavior( Scene& scene, component_id id, size_t index = 0 );

	void Destroy() override;
};

bool operator==( const Behavior& first, const Behavior& second );
