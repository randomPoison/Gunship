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
