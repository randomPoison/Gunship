#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "GameObject.h"
#include "Scene.h"

GameObject::GameObject( Scene* scene, const char* name ) :
	scene( scene ),
	name( name ),
	id( GenerateUniqueComponentID() )
{
	// setup the SceneNode for this object
	node = scene->SceneManager()->getRootSceneNode()->createChildSceneNode();
}

ComponentLocator< CameraComponent > GameObject::AddCameraComponent()
{
	cameraComponent = scene->AddCameraComponent( *this );
	return cameraComponent;
}

bool operator==( const GameObject& first, const GameObject& second )
{
	return first.id == second.id;
}

bool operator!=( const GameObject& first, const GameObject& second )
{
	return !( first == second );
}
