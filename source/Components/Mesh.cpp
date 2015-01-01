#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "Components/Mesh.h"
#include "Scene.h"

namespace Gunship
{
	namespace Components
	{
		Mesh::Mesh( const Scene& scene, Transform::Handle transform, const char* meshName )
			: mesh( nullptr ),
			  sceneManager( &scene.sceneManager() )
		{
			mesh = sceneManager->createEntity( meshName );
			transform->node->attachObject( mesh );
		}

		Mesh::~Mesh()
		{
			mesh->detachFromParent();
			sceneManager->destroyEntity( mesh );
		}
	}
}
