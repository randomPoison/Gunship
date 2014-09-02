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
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	if ( args.IsConstructCall() )
	{
		v8::String::Utf8Value name( args[0] );
		ComponentInfo info;
		if ( name.length() != 0 )
		{
			info = gunship->currentScene->AddGameObject( *name );
		}
		else
		{
			info = gunship->currentScene->AddGameObject();
		}
		GameObjectComponent* component = gunship->currentScene->FindGameObject( info );

		gameObject->Set( V8_STRING( isolate, "id" ), V8_UNSIGNED( isolate, info.id ) );
		gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );
		gameObject->Set( V8_STRING( isolate, "name" ), V8_STRING( isolate, component->name.c_str() ) );

		args.GetReturnValue().Set( gameObject );
	}
}

void GameObjectComponent::AddCameraComponent( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_CALLBACK_SCOPE();
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
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info{ V8_GET_UNSIGNED( isolate, gameObject, "id" ),
						V8_GET_UNSIGNED( isolate, gameObject, "index" ) };

	v8::String::Utf8Value mesh( args[0] );
	gunship->currentScene->AddMesh( info, *mesh );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );
}

void GameObjectComponent::SetPosition( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info{ V8_GET_UNSIGNED( isolate, gameObject, "id" ),
						V8_GET_UNSIGNED( isolate, gameObject, "index" ) };

	GameObjectComponent* component = gunship->currentScene->FindGameObject( info );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );

	component->node->setPosition( args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue() );
}

void GameObjectComponent::AddBehavior( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	printf( "argument is function: %s\n", (args[0]->IsFunction() ? "true" : "false") );

	v8::Local< v8::Function > function = v8::Local< v8::Function >::Cast( args[0] );
	v8::Persistent< v8::Object, v8::CopyablePersistentTraits< v8::Object > > _gameObject( isolate, gameObject );
	v8::Persistent< v8::Function, v8::CopyablePersistentTraits< v8::Function > > _function( isolate, function );
	gunship->currentScene->AddBehavior( _gameObject, _function );
}
