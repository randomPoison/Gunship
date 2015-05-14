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
	TransformManager& transformManager = scene.componentManager< TransformManager >();
	ColliderManager& colliderManager = scene.componentManager< ColliderManager >();
	CollisionManager& collisionManager = scene.componentManager< CollisionManager >();

	// Clear out old collisions.
	collisionManager.Clear();
	const FastArray< CollisionLayer >& collisionLayers = colliderManager.layers();

	// Handle self collisions for layers.
	for ( size_t layerIndex : colliderManager.selfCollisions() )
	{
		//SelfCollideLayer( collisionLayers[layerIndex], transformManager, collisionManager );
	}

	// Perform pair-wise collisions for all layers.
	const ColliderManager::CollisionPairs& collisionPairs = colliderManager.collisionPairs();
	const CollisionLayer* layer = collisionLayers.begin();
	for ( const FastArray< size_t >* layerCollisions = collisionPairs.begin(); layerCollisions != collisionPairs.end(); ++layerCollisions, ++layer )
	{
		for ( size_t layerIndex : *layerCollisions )
		{
			CollideLayers( *layer, collisionLayers[layerIndex], transformManager, collisionManager );
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
