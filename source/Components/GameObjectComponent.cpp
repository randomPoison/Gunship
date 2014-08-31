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
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::Isolate::Scope isolateScope( isolate );
	v8::HandleScope handleScope( isolate );

	if ( args.IsConstructCall() )
	{
		ComponentInfo info = Gunship::globalInstace->currentScene->AddGameObject();
		v8::Local< v8::Object > gameObject = args.Holder();
		gameObject->Set( v8::String::NewFromUtf8( isolate, "id" ), v8::Integer::NewFromUnsigned( isolate, info.id ) );
		gameObject->Set( v8::String::NewFromUtf8( isolate, "index" ), v8::Integer::NewFromUnsigned( isolate, info.index ) );
		args.GetReturnValue().Set( gameObject );
	}

}

void GameObjectComponent::AddCameraComponent( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::Isolate::Scope isolateScope( isolate );
	v8::HandleScope handleScope( isolate );

	v8::Local< v8::Object > gameObject = args.Holder();
	ComponentInfo info{ gameObject->Get( v8::String::NewFromUtf8( isolate, "id" ) )->IntegerValue(),
						gameObject->Get( v8::String::NewFromUtf8( isolate, "index" ) )->IntegerValue() };

	if ( !gameObject->Get( v8::String::NewFromUtf8( isolate, "hasCamera" ) )->BooleanValue() )
	{
		printf( "Adding camera to gameobject %d\n", info.id );
		Gunship::globalInstace->currentScene->AddCameraComponent( info );
		gameObject->Set( v8::String::NewFromUtf8( isolate, "hasCamera" ), v8::Boolean::New( isolate, true ) );
	}
}
