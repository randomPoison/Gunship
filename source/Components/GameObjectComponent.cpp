#include "Gunship.h"
#include "Components/GameObjectComponent.h"

GameObjectComponent::GameObjectComponent( Ogre::SceneNode* node, const char* name ) :
	id( Component::GenerateUniqueComponentID() ),
	name( name ),
	node( node )
{
}

void GameObjectComponent::CreateGameObjectComponent( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	if ( args.IsConstructCall() )
	{
		printf("Constructing game object!\n");
		ComponentInfo info = Gunship::globalInstace->currentScene->AddGameObject();
	}

}
