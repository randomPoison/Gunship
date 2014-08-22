#include "Gunship.h"
#include "Components/GameObjectComponent.h"

GameObjectComponent::GameObjectComponent( Scene* scene, Ogre::SceneNode* node, const char* name ) :
	id( Component::GenerateUniqueComponentID() ),
	name( name ),
	scene( scene ),
	node( node ),
	numBehaviors( 0 )
{
}
