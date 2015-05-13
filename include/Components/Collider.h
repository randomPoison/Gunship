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
	unsigned int layer;
	float radius;
};

struct CollisionLayer
{
	Containers::FastArray< SphereCollider > colliders;
	Containers::FastArray< Entity > entities;
	Containers::FastArray< CollisionLayer* > layersToCollide;
	bool collideSelf;

private:
	CollisionLayer& operator=( const CollisionLayer& other );
};

class ColliderManager : public ComponentManager< ColliderManager >
{
	friend class Scene;

	struct IndexPair
	{
		size_t row;
		size_t col;
	};

public:
	/// @brief Assign a sphere collider to the given entity.
	SphereCollider& Assign( Entity entity, unsigned int layer );

	/// @brief Specify a pair of layers that should be processed for collisions.
	void CollideLayers( unsigned int first, unsigned int second );

	const Containers::FastArray< CollisionLayer >& layers() const;

private:
	Gunship::Scene& _scene;

	Containers::FastArray< CollisionLayer > _layers;
	Containers::EntityMap< IndexPair > _indices;

	ColliderManager( Gunship::Scene& scene );

	void DestroyAllMarked() override;
	void DestroyAll( Entity entity ) override;
};

} }
