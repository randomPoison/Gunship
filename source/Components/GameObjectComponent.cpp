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

	ComponentInfo info
	{	V8_GET_UNSIGNED( isolate, gameObject, "id" ),
		V8_GET_UNSIGNED( isolate, gameObject, "index" )};

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

	ComponentInfo info
	{	V8_GET_UNSIGNED( isolate, gameObject, "id" ),
		V8_GET_UNSIGNED( isolate, gameObject, "index" )};

	v8::String::Utf8Value mesh( args[0] );
	gunship->currentScene->AddMesh( info, *mesh );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );
}

void GameObjectComponent::SetPosition( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info
	{	V8_GET_UNSIGNED( isolate, gameObject, "id" ),
		V8_GET_UNSIGNED( isolate, gameObject, "index" )};

	GameObjectComponent* component = gunship->currentScene->FindGameObject( info );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );

	v8::Local< v8::Float32Array > vec3 = v8::Local< v8::Float32Array >::Cast( args[0] );
	component->node->setPosition( V8_GET_FROM_VECTOR( vec3, 0 ), V8_GET_FROM_VECTOR( vec3, 1 ), V8_GET_FROM_VECTOR( vec3, 2 ) );
}

void GameObjectComponent::SetPositionByValue( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info
	{	V8_GET_UNSIGNED( isolate, gameObject, "id" ),
		V8_GET_UNSIGNED( isolate, gameObject, "index" )};

	GameObjectComponent* component = gunship->currentScene->FindGameObject( info );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );

	component->node->setPosition( args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue() );
}

void GameObjectComponent::Translate( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info
	{	V8_GET_UNSIGNED( isolate, gameObject, "id" ),
		V8_GET_UNSIGNED( isolate, gameObject, "index" )};

	GameObjectComponent* component = gunship->currentScene->FindGameObject( info );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );

	v8::Local< v8::Float32Array > vec3 = v8::Local< v8::Float32Array >::Cast( args[0] );
	component->node->translate( V8_GET_FROM_VECTOR( vec3, 0 ), V8_GET_FROM_VECTOR( vec3, 1 ), V8_GET_FROM_VECTOR( vec3, 2 ) );
}

void GameObjectComponent::TranslateByValue( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info
	{	V8_GET_UNSIGNED( isolate, gameObject, "id" ),
		V8_GET_UNSIGNED( isolate, gameObject, "index" )};

	GameObjectComponent* component = gunship->currentScene->FindGameObject( info );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );

	component->node->translate( args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue() );
}

void GameObjectComponent::SetScale( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info
	{	V8_GET_UNSIGNED( isolate, gameObject, "id" ),
		V8_GET_UNSIGNED( isolate, gameObject, "index" )};

	GameObjectComponent* component = gunship->currentScene->FindGameObject( info );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );

	v8::Local< v8::Float32Array > vec3 = v8::Local< v8::Float32Array >::Cast( args[0] );
	component->node->setScale( V8_GET_FROM_VECTOR( vec3, 0 ), V8_GET_FROM_VECTOR( vec3, 1 ), V8_GET_FROM_VECTOR( vec3, 2 ) );
}

void GameObjectComponent::SetScaleByValue( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info
	{	V8_GET_UNSIGNED( isolate, gameObject, "id" ),
		V8_GET_UNSIGNED( isolate, gameObject, "index" )};

	GameObjectComponent* component = gunship->currentScene->FindGameObject( info );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );

	component->node->setScale( args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue() );
}

void GameObjectComponent::GetPosition( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	V8_CALLBACK_SCOPE();
	V8_CALLBACK_INIT(args);

	ComponentInfo info
	{	V8_GET_UNSIGNED( isolate, gameObject, "id" ),
		V8_GET_UNSIGNED( isolate, gameObject, "index" )};

	GameObjectComponent* component = gunship->currentScene->FindGameObject( info );
	gameObject->Set( V8_STRING( isolate, "index" ), V8_UNSIGNED( isolate, info.index ) );

	v8::Local< v8::Float32Array > vec3 = v8::Local< v8::Float32Array >::Cast( args[0] );
	Ogre::Vector3 pos = component->node->getPosition();
	vec3->Set( 0, V8_NUMBER( isolate, pos.x ) );
	vec3->Set( 1, V8_NUMBER( isolate, pos.y ) );
	vec3->Set( 2, V8_NUMBER( isolate, pos.z ) );

	args.GetReturnValue().Set( vec3 );
}
