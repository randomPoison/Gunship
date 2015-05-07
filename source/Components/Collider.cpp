#include <SDL_assert.h>	

#include "Scene.h"
#include "Components/Collider.h"

using Gunship::Scene;

namespace Gunship {
namespace Components {

ColliderManager::ColliderManager( Scene& scene )
	: _scene( scene )
{
}

SphereCollider& ColliderManager::Assign( Entity entity )
{
	SDL_assert_paranoid( !_indices.Contains( entity ) );

	// TODO: Ensure the entity has a transform component.

	size_t index = _colliders.count();
	SphereCollider& collider = _colliders.Push( SphereCollider() );
	_entities.Push( entity );
	_indices.Put( entity, index );

	return collider;
}

const Containers::FastArray< SphereCollider >& ColliderManager::colliders() const
{
	return _colliders;
}

const Containers::FastArray< Entity >& ColliderManager::entities() const
{
	return _entities;
}

void ColliderManager::DestroyAllMarked() {}
void ColliderManager::DestroyAll( Entity entity ) {}

} }
