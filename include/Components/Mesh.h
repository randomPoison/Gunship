#pragma once

#include <entityx/Entity.h>

#include "Components/Transform.h"

namespace Ogre
{
	class Entity;
}

namespace Gunship
{
	class Scene;

	namespace Components
	{
		struct Mesh : entityx::Component< Mesh >
		{
			Mesh( const Scene& scene,
			      Transform::Handle transform,
			      const char* meshName );

			Ogre::Entity* mesh;
		};
	}
}
