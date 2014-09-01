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
	V8_ENTER_SCOPE();
	V8_CALLBACK_INIT(args);

	if ( args.IsConstructCall() )
	{
		ComponentInfo info = gunship->currentScene->AddGameObject();

		gameObject->Set( V8_STRING( isolate, "id" ), V8_UNSIGNED( isolate, info.id ) );
		gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );
		args.GetReturnValue().Set( gameObject );
	}
}

void GameObjectComponent::AddCameraComponent( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_ENTER_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info{ V8_GET_UNSIGNED( isolate, gameObject, "id" ),
						V8_GET_UNSIGNED( isolate, gameObject, "index" ) };

	if ( !gameObject->Get( V8_STRING( isolate, "hasCamera" ) )->BooleanValue() )
	{
		gunship->currentScene->AddCameraComponent( info );
		gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );
		gameObject->Set( V8_STRING( isolate, "hasCamera" ), V8_BOOL( isolate, true ) );
	}
}


void GameObjectComponent::AddMesh( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_ENTER_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info{ V8_GET_UNSIGNED( isolate, gameObject, "id" ),
						V8_GET_UNSIGNED( isolate, gameObject, "index" ) };

	gunship->currentScene->AddMesh( info, "ColourCube" );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );
}

void GameObjectComponent::SetPosition( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_ENTER_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info{ V8_GET_UNSIGNED( isolate, gameObject, "id" ),
						V8_GET_UNSIGNED( isolate, gameObject, "index" ) };

	GameObjectComponent* component = gunship->currentScene->FindGameObject( info );
	component->node->setPosition( 0.0f, 0.0f, 10.0f );
	component->node->lookAt( Ogre::Vector3( 0.0f, 0.0f, 0.0f ), Ogre::Node::TS_WORLD );
}

