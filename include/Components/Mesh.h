#pragma once

#include "Components/SimpleStructComponent.h"
#include "Components/SimpleStructComponentManager.h"

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
			      const Transform& transform,
			      const char* meshName );

			~Mesh();
		};

		class MeshManager : public SimpleStructComponentManager< Mesh >
		{
		public:
			MeshManager( Scene& scene );

			Mesh& Assign( Entity::ID entity, const char* meshName );

		private:

			using SimpleStructComponentManager< Mesh >::Assign;

			Scene& _scene;
		};
	}
}
