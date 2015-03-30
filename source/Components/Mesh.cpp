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

		Mesh::~Mesh()
		{
			mesh->detachFromParent();
			sceneManager->destroyEntity( mesh );
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
