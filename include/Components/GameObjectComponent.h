#pragma once

#include <string>

struct GameObjectComponent
{
	component_id id;
	std::string name;

	Ogre::SceneNode* node;

	GameObjectComponent( Ogre::SceneNode* node, const char* name );

	static void CreateGameObjectComponent( const v8::FunctionCallbackInfo< v8::Value >& args );
	static void AddCameraComponent( const v8::FunctionCallbackInfo< v8::Value >& args );
	static void AddMesh( const v8::FunctionCallbackInfo< v8::Value >& args );

	static void SetPosition( const v8::FunctionCallbackInfo< v8::Value >& args );
	static void SetPositionByValue( const v8::FunctionCallbackInfo< v8::Value >& args );
	static void Translate( const v8::FunctionCallbackInfo< v8::Value >& args );
	static void TranslateByValue( const v8::FunctionCallbackInfo< v8::Value >& args );
	static void SetScale( const v8::FunctionCallbackInfo< v8::Value >& args );
	static void SetScaleByValue( const v8::FunctionCallbackInfo< v8::Value >& args );

	static void GetPosition( const v8::FunctionCallbackInfo< v8::Value >& args );
};
