#pragma once

#include <string>

struct GameObjectComponent
{
	component_id id;
	std::string name;

	Ogre::SceneNode* node;

	GameObjectComponent( Ogre::SceneNode* node, const char* name = "Game Object" );

	static void CreateGameObjectComponent( const v8::FunctionCallbackInfo< v8::Value >& args );
	static void AddCameraComponent( const v8::FunctionCallbackInfo< v8::Value >& args );
};
