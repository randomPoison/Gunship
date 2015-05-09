#include "Components/Collision.h"

namespace Gunship {
namespace Components {

void CollisionManager::DestroyAllMarked() {}

void CollisionManager::DestroyAll( Entity entity ) {}

const CollisionManager::CollisionList& CollisionManager::collisions() const
{
	return _collisionData;
}

void CollisionManager::Add( Entity first, Entity second )
{
	CollisionData data;
	data.first = first;
	data.second = second;

	_collisionData.Push( data );
}

void CollisionManager::Clear()
{
	_collisionData.Clear();
}

}
}
