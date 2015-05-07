#pragma once

#include "Entity/ComponentManager.h"
#include "Entity/Entity.h"
#include "Containers/FastArray.h"
#include "Containers/EntityMap.h"

namespace Gunship {

class Scene;

namespace Components {

struct SphereCollider
{
	float radius = 1.0f;
};

class ColliderManager : public ComponentManager< ColliderManager >
{
	friend class Scene;

public:
	/// @brief Assign a sphere collider to the given entity.
	SphereCollider& Assign( Entity entity );

	const Containers::FastArray< SphereCollider >& colliders() const;
	const Containers::FastArray< Entity >& entities() const;

private:
	Gunship::Scene& _scene;

	Containers::FastArray< SphereCollider > _colliders;
	Containers::FastArray< Entity > _entities;
	Containers::EntityMap< size_t > _indices;

	ColliderManager( Gunship::Scene& scene );

	void DestroyAllMarked() override;
	void DestroyAll( Entity entity ) override;
};

} }
