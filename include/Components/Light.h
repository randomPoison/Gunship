#pragma once

#include <entityx/Entity.h>

#include "Components/Transform.h"

namespace Ogre
{
	class Light;
}

namespace Gunship
{
	class Scene;

	namespace Components
	{
		struct Light : public entityx::Component< Light >
		{
			Light( const Scene& scene, const Transform::Handle& transform );

			Ogre::Light* light;
		};
	}
}
