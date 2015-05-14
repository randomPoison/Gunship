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

struct CollisionLayer : NonCopyable
{
	Containers::FastArray< SphereCollider > colliders;
	Containers::FastArray< Entity > entities;
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
	typedef Containers::FastArray< Containers::FastArray< size_t > > CollisionPairs;

	/// @brief Assign a sphere collider to the given entity.
	SphereCollider& Assign( Entity entity, unsigned int layer );

	/// @brief Increase the layer count if it is less than the specified count.
	///
	/// @note
	///     This will not decrease the number of layers if it is more than \a layerCount.
	void SetLayerCount( size_t layerCount );

	/// @brief Specify whether a pair of layers should be checked for collisions.
	void SetCollision( unsigned int first, unsigned int second, bool collide );

	const Containers::FastArray< CollisionLayer >& layers() const;
	const CollisionPairs& collisionPairs() const;
	const Containers::FastArray< size_t >& selfCollisions() const;

	/// @brief Returns the number of supported layers.
	size_t layerCount() const;

private:
	Gunship::Scene& _scene;

	Containers::FastArray< CollisionLayer > _layers;
	Containers::EntityMap< IndexPair > _indices;

	/// @brief A 2D array where each row is the list of collision partners for that layer.
	///
	/// @todo
	///     FastArray is not safe for the outer list because it doesn't call destructors of its
	///     elements when destroyed, so it will leak the memory of all the inner arrays.
	CollisionPairs _collisionPairs;
	Containers::FastArray< size_t > _selfCollisions;

	ColliderManager( Gunship::Scene& scene );

	void DestroyAllMarked() override;
	void DestroyAll( Entity entity ) override;
};

} }
