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
	ColliderManager& colliderManager = scene.componentManager< ColliderManager >();
	CollisionManager& collisionManager = scene.componentManager< CollisionManager >();

	// Clear out old collisions.
	collisionManager.Clear();
	const FastArray< CollisionLayer >& collisionLayers = colliderManager.layers();

	// Update the colliders' cached transforms.
	colliderManager.UpdateCachedPositions();

	// Handle self collisions for layers.
	for ( size_t layerIndex : colliderManager.selfCollisions() )
	{
		SelfCollideLayer( collisionLayers[layerIndex], collisionManager );
	}

	// Perform pair-wise collisions for all layers.
	const ColliderManager::CollisionPairs& collisionPairs = colliderManager.collisionPairs();
	const CollisionLayer* layer = collisionLayers.begin();
	for ( const FastArray< size_t >* layerCollisions = collisionPairs.begin(); layerCollisions != collisionPairs.end(); ++layerCollisions, ++layer )
	{
		for ( size_t layerIndex : *layerCollisions )
		{
			CollideLayers( *layer, collisionLayers[layerIndex], collisionManager );
		}
	}
}

bool SphereCollision(
	const SphereCollider& first,
	const SphereCollider& second )
{
	float distanceSqr = first._cachedPosition.squaredDistance( second._cachedPosition );
	float a = first.radius;
	float b = first.radius;
	float colliderDistanceSqr = a * a + 2 * a * b + b * b;
	return distanceSqr <= colliderDistanceSqr;
}

void CollisionSystem::CollideLayers(
	const CollisionLayer& firstLayer,
	const CollisionLayer& secondLayer,
	CollisionManager& collisionManager )
{
	const SphereCollider* firstCollider = firstLayer.colliders.begin();
	const Entity* firstEntity = firstLayer.entities.begin();
	for ( ; firstCollider != firstLayer.colliders.end(); ++firstCollider, ++firstEntity )
	{
		const SphereCollider* secondCollider = secondLayer.colliders.begin();
		const Entity* secondEntity = secondLayer.entities.begin();
		for ( ; secondCollider != secondLayer.colliders.end(); ++secondCollider, ++secondEntity )
		{
			if ( SphereCollision( *firstCollider, *secondCollider ) )
			{
				collisionManager.Add( *firstEntity, *secondEntity );
			}
		}
	}
}

void CollisionSystem::SelfCollideLayer(
	const Components::CollisionLayer& layer,
	Components::CollisionManager& collisionManager )
{
	const SphereCollider* firstCollider = layer.colliders.begin();
	const Entity* firstEntity = layer.entities.begin();
	for ( ; firstCollider != layer.colliders.end() - 1; ++firstCollider, ++firstEntity )
	{
		const SphereCollider* secondCollider = firstCollider + 1;
		const Entity* secondEntity = firstEntity + 1;
		for ( ; secondCollider != layer.colliders.end(); ++secondCollider, ++secondEntity )
		{
			if ( SphereCollision( *firstCollider, *secondCollider ) )
			{
				collisionManager.Add( *firstEntity, *secondEntity );
			}
		}
	}
}

}
}
