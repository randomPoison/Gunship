#include "Systems/CollisionSystem.h"
#include "Components/Transform.h"
#include "Components/Collider.h"
#include "Components/Collision.h"
#include "Scene.h"
#include "Math/Vector3.h"

using Gunship::Components::TransformManager;
using Gunship::Components::Transform;
using Gunship::Components::ColliderManager;
using Gunship::Components::CollisionManager;
using Gunship::Components::CollisionLayer;
using Gunship::Components::SphereCollider;
using Gunship::Containers::FastArray;

namespace Gunship {
namespace Systems {

void CollisionSystem::Update( Scene& scene, float delta )
{
	auto& transformManager = scene.componentManager< TransformManager >();
	auto& colliderManager = scene.componentManager< ColliderManager >();
	auto& collisionManager = scene.componentManager< CollisionManager >();

	// Clear out old collisions.
	collisionManager.Clear();

	// Perform pair-wise collisions on all components colliders.
	const FastArray< CollisionLayer >& layers = colliderManager.layers();
	for ( const CollisionLayer* layer = layers.begin(); layer != layers.end(); ++layer )
	{
		// TODO: Collide layer with self if necessary.

		for ( auto secondLayer = layer->layersToCollide.begin(); secondLayer != layer->layersToCollide.end(); ++secondLayer )
		{
			CollideLayers( *layer, **secondLayer, transformManager, collisionManager );
		}
	}
}

void CollisionSystem::CollideLayers( const CollisionLayer& firstLayer, const CollisionLayer& secondLayer, TransformManager& transformManager, CollisionManager& collisionManager )
{
	const SphereCollider* firstCollider = firstLayer.colliders.begin();
	const Entity* firstEntity = firstLayer.entities.begin();
	for ( ; firstCollider != firstLayer.colliders.end(); ++firstCollider, ++firstEntity )
	{
		Transform& firstTransform = transformManager.Get( *firstEntity );

		const SphereCollider* secondCollider = secondLayer.colliders.begin();
		const Entity* secondEntity = secondLayer.entities.begin();
		for ( ; secondCollider != secondLayer.colliders.end(); ++secondCollider, ++secondEntity )
		{
			Transform& secondTransform = transformManager.Get( *secondEntity );

			Vector3 position = firstTransform.position();
			Vector3 otherPosition = secondTransform.position();

			float distanceSqr = position.squaredDistance( otherPosition );
			float a = firstCollider->radius;
			float b = secondCollider->radius;
			float colliderDistanceSqr = a * a + 2 * a * b + b * b;
			if ( distanceSqr <= colliderDistanceSqr )
			{
				collisionManager.Add( *firstEntity, *secondEntity );
			}
		}
	}
}

}
}
