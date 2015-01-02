#pragma once

#include "Components/SimpleStructComponent.h"

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
		struct Transform;

		/**
		 * @brief Component representing a mesh resource.
		 */
		struct Mesh : public SimpleStructComponent
		{
			Ogre::Entity* mesh;
			Ogre::SceneManager* sceneManager;

			Mesh( const Scene& scene,
			      const Transform* transform,
			      const char* meshName );

			~Mesh();
		};
	}
}
