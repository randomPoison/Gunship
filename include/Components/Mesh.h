#pragma once

#include <entityx/Entity.h>

#include "Components/Transform.h"

namespace Ogre
{
	class Entity;
	class SceneManager;
}

namespace Gunship
{
	class Scene;

	namespace Components
	{
		/**
		 * @brief Component representing a mesh resource.
		 */
		struct Mesh : entityx::Component< Mesh >
		{
			Ogre::Entity* mesh;

			Mesh( const Scene& scene,
			      Transform::Handle transform,
			      const char* meshName );
		};
	}
}
