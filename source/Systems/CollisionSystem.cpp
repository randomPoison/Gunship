#include "Systems/CollisionSystem.h"
#include "Components/Transform.h"
#include "Components/Collider.h"
#include "Scene.h"
#include "Math/Vector3.h"

using Gunship::Components::TransformManager;
using Gunship::Components::ColliderManager;

namespace Gunship {
namespace Systems {

void CollisionSystem::Update( Scene& scene, float delta )
{
	auto& transformManager = scene.componentManager< TransformManager >();
	auto& colliderManager = scene.componentManager< ColliderManager >();

	// Perform pair-wise collisions on all components colliders.
	auto& colliders = colliderManager.colliders();
	auto& entities = colliderManager.entities();

	auto collider = colliders.begin();
	auto entity = entities.begin();
	for ( ; collider != colliders.end() - 1 && entity != entities.end() - 1; ++collider, ++entity )
	{
		auto& transform = transformManager.Get( *entity );

		auto otherCollider = collider + 1;
		auto otherEntity = entity + 1;
		for ( ; otherCollider != colliders.end() && otherEntity != entities.end(); ++otherCollider, ++otherEntity )
		{
			auto& otherTransform = transformManager.Get( *otherEntity );

			Vector3 position = transform.position();
			Vector3 otherPosition = otherTransform.position();

			float distanceSqr = position.squaredDistance( otherPosition );
			float a = collider->radius;
			float b = otherCollider->radius;
			float colliderDistanceSqr = a * a + 2 * a * b + b * b;
			if ( distanceSqr <= colliderDistanceSqr )
			{
				// TODO: Notify of collision.
			}
		}
	}
}

}
}
