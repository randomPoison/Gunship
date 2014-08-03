#pragma once

#include <string>

namespace Ogre
{
	class SceneNode;
}

class Scene;

#include "components/Component.h"
#include "components/CameraComponent.h"

class GameObject
{
public:
	GameObject( Scene* scene, const char* name = "Game Object" );

	ComponentLocator< CameraComponent > AddCameraComponent();
	void AddMesh( const char* name, const char* mesh );

	void LookAt( float x, float y, float z );
	void Translate( float x, float y, float z );
	void SetPosition( float x, float y, float z );

private:
	ComponentLocator< CameraComponent > cameraComponent;

	Scene* scene;
	Ogre::SceneNode* node;

	std::string name;
	component_id id;

	friend class Scene;
	friend bool operator==( const GameObject& first, const GameObject& second );
	friend bool operator!=( const GameObject& first, const GameObject& second );
};

bool operator==( const GameObject& first, const GameObject& second );
bool operator!=( const GameObject& first, const GameObject& second );
