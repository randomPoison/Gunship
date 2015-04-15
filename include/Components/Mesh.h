#pragma once

#include <vector>        ///< @todo Remove dependence on STL containers.
#include <unordered_map> ///< @todo Remove dependence on STL containers.

#include "Entity/ComponentManager.h"
#include "Components/SimpleStructComponent.h"
#include "Containers/EntityMap.h"

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
			std::vector< Mesh >* meshPool; ///< @todo This shouldn't be necessary, find a way to get rid of it. Also, it shouldn't be null so maybe a pointer isn't a good idea?
		};

		class MeshManager : public ComponentManager< MeshManager >
		{

		public:
			MeshManager( Scene& scene );

			Mesh& Assign( Entity::ID entityID, const char* meshName );

			void Destroy( Entity::ID entityID );

			const std::vector< Mesh > components() const;

		private:
			Scene& _scene;

			std::vector< Mesh > _meshes;
			std::vector< Entity::ID > _entities;
			Containers::EntityMap< size_t > _indices;

			std::vector< Entity::ID > _markedForDestruction;
			std::unordered_map< Ogre::String, std::vector< Mesh > > _pooledMeshes;

			void DestroyAll( Entity::ID entityID ) override;
			void DestroyAllMarked() override;

			void DestroyImmediate( Entity::ID entityID );
		};
	}
}
