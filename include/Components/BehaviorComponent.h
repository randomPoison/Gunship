#pragma once

struct BehaviorComponent : public Component
{
public:
	BehaviorComponent( GameObject& owner, BehaviorFunction function );

	BehaviorFunction behavior;
};
