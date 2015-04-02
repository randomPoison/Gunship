#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include <SDL_assert.h>

#include "Scene.h"
#include "Components/Mesh.h"
#include "Components/Transform.h"

namespace Gunship
{
	namespace Components
	{
		Mesh::Mesh( const Scene& scene, const Transform& transform, const char* meshName )
			: mesh( nullptr ),
			  sceneManager( &scene.sceneManager() )
		{
			mesh = sceneManager->createEntity( meshName );
			transform.node->attachObject( mesh );
		}

		Mesh::Mesh( Mesh&& original )
		{
			MoveOutOf( original );
		}

		Mesh& Mesh::operator=( Mesh&& original )
		{
			MoveOutOf( original );

			return *this;
		}

		Mesh::~Mesh()
		{
			if ( mesh != nullptr && sceneManager != nullptr )
			{
				mesh->detachFromParent();
				sceneManager->destroyEntity( mesh );
			}
		}

		void Mesh::MoveOutOf( Mesh& original )
		{
			entityID = original.entityID;

			mesh = original.mesh;
			sceneManager = original.sceneManager;

			original.mesh = nullptr;
			original.sceneManager = nullptr;
		}

		MeshManager::MeshManager( Scene& scene )
			: _scene( scene )
		{
		}

		Mesh& MeshManager::Assign( Entity::ID entity, const char* meshName )
		{
			return static_cast< Mesh& >( Assign(
				entity,
				_scene,
				_scene.componentManager< TransformManager >().Get( entity ),
				meshName ) );
		}
	}
}
