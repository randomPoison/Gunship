#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "Gunship.h"

#include "GameObject.h"

GameObjectComponent::GameObjectComponent( Scene* scene, Ogre::SceneNode* node, const char* name ) :
	scene( scene ),
	name( name ),
	id( GenerateUniqueComponentID() ),
	node( node )
{
}

GameObject::GameObject( Scene* scene, component_id id, size_t index ) : ComponentLocator( scene, id, index )
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

Behavior GameObject::AddBehavior( BehaviorFunction behavior )
{
	return scene->AddBehaviorComponent( *this, behavior );
}

void GameObject::LookAt( float x, float y, float z )
{
	scene->FindComponent( *this )->node->lookAt( Ogre::Vector3( x, y , z ), Ogre::Node::TS_WORLD );
}

void GameObject::LookAt( GameObject& target )
{
	GameObjectComponent* targetComponent = scene->FindComponent( target );
	scene->FindComponent( *this )->node->lookAt( targetComponent->node->getPosition(), Ogre::Node::TS_WORLD );
}

void GameObject::Translate( float x, float y, float z )
{
	scene->TranslateGameObject( *this, x, y, z );
}

void GameObject::SetPosition( float x, float y, float z )
{
	scene->FindComponent( *this )->node->setPosition( x, y, z );
}

void GameObject::SetScale( float x, float y, float z )
{
	scene->FindComponent( *this )->node->scale( Ogre::Vector3( x, y, z ) );
}

Ogre::Vector3 GameObject::Position()
{
	Ogre::SceneNode* node = scene->FindComponent( *this )->node;
	return node->_getDerivedPosition();
}

size_t GameObject::LastIndex() const
{
	return index;
}

void GameObject::AddChild( GameObject& gameObject )
{
	Ogre::Node* thisNode = scene->FindComponent( *this )->node;
	Ogre::Node* otherNode = scene->FindComponent( gameObject )->node;

	otherNode->getParent()->removeChild( otherNode );
	thisNode->addChild( otherNode );
}
