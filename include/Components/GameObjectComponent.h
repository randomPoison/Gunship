#pragma once

#include <string>

struct GameObjectComponent
{
	GameObjectComponent( Scene* scene, Ogre::SceneNode* node, const char* name = "Game Object" );

	component_id id;
	std::string name;

	Scene* scene;
	Ogre::SceneNode* node;

	size_t numBehaviors;
};
