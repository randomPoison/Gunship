#pragma once

#include "Entity/ComponentManager.h"
#include "Containers/FastArray.h"

namespace Gunship {

namespace Systems
{
	class CollisionSystem;
}

namespace Components {

struct CollisionData
{
	Entity first;
	Entity second;
};

class CollisionManager : public ComponentManager< CollisionManager >
{
	friend class Systems::CollisionSystem;

public:
	typedef Containers::FastArray< CollisionData > CollisionList;

	void DestroyAllMarked() override;
	void DestroyAll( Entity entity ) override;

	const CollisionList& collisions() const;

private:
	CollisionList _collisionData;

	void Add( Entity first, Entity second );
	void Clear();
};

}
}
