#pragma once

#include "Entity/Entity.h"
#include "Utility/MoveOnly.h"

namespace Gunship
{
	namespace Components
	{
		struct SimpleStructComponent : public MoveOnly
		{
			Entity::ID entityID;
		};
	}
}
