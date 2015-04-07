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
		public:
			Ogre::Entity* mesh;

			/// @todo This can be taken out if we write a custom manager that handles component destruction.
			Ogre::SceneManager* sceneManager;

			Mesh( const Scene& scene,
			      const Transform& transform,
			      const char* meshName );
			Mesh( Mesh&& original );
			Mesh& operator=( Mesh&& original );
			~Mesh();

		private:
			void MoveOutOf( Mesh& original );
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
