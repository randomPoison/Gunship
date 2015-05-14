#pragma once

#include "Entity/System.h"

namespace Gunship {

namespace Components
{
	class TransformManager;
	class CollisionManager;
	struct CollisionLayer;
}

namespace Systems {

class CollisionSystem : public System< CollisionSystem >
{
public:
	void Update( Scene& scene, float delta ) override;

private:
	void CollideLayers( const Components::CollisionLayer& firstLayer, const Components::CollisionLayer& secondLayer, Components::TransformManager& transformManager, Components::CollisionManager& collisionManager );
	void SelfCollideLayer( const Components::CollisionLayer& layer, Components::TransformManager& transformManager, Components::CollisionManager& collisionManager );
};

}
}
