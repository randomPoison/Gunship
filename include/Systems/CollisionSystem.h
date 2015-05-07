#pragma once

#include "Entity/System.h"

namespace Gunship {
namespace Systems {

class CollisionSystem : public System< CollisionSystem >
{
public:
	void Update( Scene& scene, float delta ) override;
};

}
}
