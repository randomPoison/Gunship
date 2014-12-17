#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreResourceManager.h>
#include <OgreSceneNode.h>

#include "Components/Mesh.h"
#include "Scene.h"

Gunship::Mesh::Mesh( const Scene& scene, const Transform::Handle& transform, const char* meshName )
	: entity( nullptr )
{
	entity = scene.sceneManager().createEntity( meshName );
	transform->node->attachObject( entity );
}
