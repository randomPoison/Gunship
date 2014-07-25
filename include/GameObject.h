#pragma once

#include <string>

namespace Ogre
{
	class SceneNode;
}

#include "Scene.h"
#include "components/Component.h"
#include "components/CameraComponent.h"

class GameObject
{
public:
	GameObject( Scene* scene, const char* baseName = "Game Object" );

	~GameObject() { };

protected:
	ComponentLocator< CameraComponent > cameraComponet;

	Scene* scene;
	Ogre::SceneNode* node;

	std::string name;
	std::string id;

private:
	static std::string GenerateUniqueID( const char* base );
};
