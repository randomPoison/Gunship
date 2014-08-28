#pragma once

struct ColliderComponent : Component
{
	ColliderComponent( GameObject& owner, float radius );

	float radius;

	static bool Collide( ColliderComponent& first, ColliderComponent& second );
};
