#include <SDL_assert.h>	

#include "Scene.h"
#include "Components/Collider.h"

using Gunship::Scene;

namespace Gunship {
namespace Components {

ColliderManager::ColliderManager( Scene& scene )
	: _scene( scene ),
	  _layers( 32 )
{
	_layers.FillToCount( 32 );
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

void ColliderManager::CollideLayers( unsigned int first, unsigned int second )
{
	// TODO: Handle self collision?
	// TODO: Out of bounds layers?

	_layers[first].layersToCollide.Push( &_layers[second] );
}

const Containers::FastArray< CollisionLayer >& ColliderManager::layers() const
{
	return _layers;
}

void ColliderManager::DestroyAllMarked() {}
void ColliderManager::DestroyAll( Entity entity ) {}

} }
