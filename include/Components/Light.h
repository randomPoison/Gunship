#pragma once

#include "Components/SimpleStructComponent.h"

namespace Ogre
{
	class Light;
}

namespace Gunship
{
	class Scene;

	namespace Components
	{
		struct Transform;

		struct Light : public SimpleStructComponent
		{
			Light( const Scene& scene, const Transform* transform );

			Ogre::Light* light;
		};
	}
}
