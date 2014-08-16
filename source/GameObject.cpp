#include "Gunship.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent( Scene* scene, Ogre::SceneNode* node, const char* name ) :
	scene( scene ),
	node( node ),
	name( name ),
	id( GenerateUniqueComponentID() )
{
}

GameObject::GameObject( Scene* scene, Ogre::SceneNode* node, component_id id, size_t index ) :
	ComponentLocator( scene, id, index ),
	node( node )
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
	node->lookAt( Ogre::Vector3( x, y , z ), Ogre::Node::TS_WORLD );
}

void GameObject::LookAt( GameObject& target )
{
	Ogre::SceneNode* targetNode = scene->FindComponent( target )->node;
	node->lookAt( targetNode->_getDerivedPosition(), Ogre::Node::TS_WORLD );
}

void GameObject::Translate( float x, float y, float z )
{
	node->translate( x, y, z );
}

void GameObject::Translate( Ogre::Vector3 translation )
{
	node->translate( translation );
}

void GameObject::SetPosition( float x, float y, float z )
{
	node->setPosition( x, y, z );
}

void GameObject::SetPosition( Ogre::Vector3 pos )
{
	node->setPosition( pos );
}

void GameObject::SetScale( float x, float y, float z )
{
	node->scale( Ogre::Vector3( x, y, z ) );
}

Ogre::Vector3 GameObject::Position()
{
	return node->_getDerivedPosition();
}

size_t GameObject::LastIndex() const
{
	return index;
}

void GameObject::AddChild( GameObject& gameObject )
{
	Ogre::Node* otherNode = scene->FindComponent( gameObject )->node;

	otherNode->getParent()->removeChild( otherNode );
	node->addChild( otherNode );
}
