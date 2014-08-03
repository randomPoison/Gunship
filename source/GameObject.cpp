#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>

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

void GameObject::LookAt( float x, float y, float z )
{
	node->lookAt( Ogre::Vector3( x, y , z ), Ogre::Node::TS_WORLD );
}

void GameObject::Translate( float x, float y, float z )
{
	node->translate( x, y, z );
}

void GameObject::SetPosition( float x, float y, float z )
{
	node->setPosition( x, y, z );
}

bool operator==( const GameObject& first, const GameObject& second )
{
	return first.id == second.id;
}

bool operator!=( const GameObject& first, const GameObject& second )
{
	return !( first == second );
}
