#include <SDL_assert.h>	

#include "Scene.h"
#include "Components/Collider.h"
#include "Components/Transform.h"

using Gunship::Scene;
using Gunship::Containers::FastArray;
using Gunship::Components::TransformManager;

namespace Gunship {
namespace Components {

ColliderManager::ColliderManager( Scene& scene )
	: _scene( scene )
{
	SetLayerCount( 32 );
}

SphereCollider& ColliderManager::Assign( Entity entity, unsigned int layer )
{
	SDL_assert_paranoid( !_indices.Contains( entity ) );

	// TODO: Ensure the entity has a transform component.

	CollisionLayer& collisionLayer = _layers[layer];
	size_t index = collisionLayer.colliders.count();
	SphereCollider& collider = collisionLayer.colliders.Push( SphereCollider() );
	collisionLayer.entities.Push( entity );

	IndexPair indices{ layer, index };
	_indices.Put( entity, indices );

	return collider;
}

void ColliderManager::SetLayerCount( size_t layerCount )
{
	// Ignore requests to decreate the number of layers.
	if ( _layers.count() >= layerCount ) return;

	// Ensure that there are enough layers.
	_layers.FillToCount( layerCount );
	_collisionPairs.FillToCount( layerCount );
}

void ColliderManager::SetCollision( unsigned int first, unsigned int second, bool collide )
{
	SDL_assert_paranoid( first < _layers.count() );
	SDL_assert_paranoid( second < _layers.count() );
	SDL_assert_paranoid( first <= second ); // TODO: Automatically handle misordered collision requrests.

	// Handle self collisions
	if ( first == second )
	{
		size_t index;
		if ( collide && !_selfCollisions.Contains( first, &index ) )
		{
			_selfCollisions.Push( first );
		}
		else if ( !collide && _selfCollisions.Contains( first, &index ) )
		{
			_selfCollisions.SwapRemove( index );
		}

		return;
	}

	// Register the collision pair.
	FastArray< size_t >& layerCollisions = _collisionPairs[first];
	size_t index;
	if ( collide && !layerCollisions.Contains( second, &index ) )
	{
		layerCollisions.Push( second );
	}
	else if ( !collide && layerCollisions.Contains( second, &index ) )
	{
		layerCollisions.SwapRemove( index );
	}
}

const Containers::FastArray< CollisionLayer >& ColliderManager::layers() const
{
	return _layers;
}

const ColliderManager::CollisionPairs& ColliderManager::collisionPairs() const
{
	return _collisionPairs;
}

const Containers::FastArray< size_t >& ColliderManager::selfCollisions() const
{
	return _selfCollisions;
}

void ColliderManager::UpdateCachedPositions()
{
	TransformManager& transformManager = _scene.componentManager< TransformManager >();

	for ( CollisionLayer* layer = _layers.begin(); layer != _layers.end(); ++layer )
	{
		Entity* entity = layer->entities.begin();
		for ( SphereCollider* collider = layer->colliders.begin(); collider != layer->colliders.end(); ++collider, ++entity )
		{
			collider->_cachedPosition = transformManager.Get( *entity ).position();
		}
	}
}

void ColliderManager::DestroyAllMarked() {}
void ColliderManager::DestroyAll( Entity entity ) {}

} }
