#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "GameObject.h"

GameObject::GameObject( Scene* scene, const char* name ) :	scene( scene ),
															name( name ),
															id( GenerateUniqueID( name ) )
{
	// setup the SceneNode for this object
	node = scene->SceneManager()->getRootSceneNode()->createChildSceneNode();
}

std::string GameObject::GenerateUniqueID( const char* base )
{
	static int offset;
	return std::string( base ) + "_" + std::to_string( offset );
}
