#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "components/Component.h"
#include "components/CameraComponent.h"
#include "Scene.h"

#include "GameObject.h"

GameObjectComponent::GameObjectComponent( Scene* scene, Ogre::SceneNode* node, const char* name ) :
	scene( scene ),
	name( name ),
	id( GenerateUniqueComponentID() ),
	node( node )
{
}

GameObject::GameObject( Scene& scene, component_id id, size_t index ) : ComponentLocator( &scene, id, index )
{
}

Camera GameObject::AddCamera()
{
	return scene->AddCameraComponent( *this );
}

void GameObject::AddMesh( const char* name, const char* mesh )
{
	scene->AddMeshToGameObject( *this, name, mesh );
}

void GameObject::LookAt( float x, float y, float z )
{
	scene->SetGameObjectLook( *this, x, y, z );
}

void GameObject::Translate( float x, float y, float z )
{
	scene->TranslateGameObject( *this, x, y, z );
}

void GameObject::SetPosition( float x, float y, float z )
{
	scene->SetGameObjectPosition( *this, x, y, z );
}

size_t GameObject::LastIndex() const
{
	return index;
}
