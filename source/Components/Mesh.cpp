#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "Scene.h"
#include "Components/Mesh.h"
#include "Components/Transform.h"

namespace Gunship
{
	namespace Components
	{
		Mesh::Mesh( const Scene& scene, const Transform* transform, const char* meshName )
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
