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

protected:
	ComponentLocator< CameraComponent > cameraComponet;

	Scene* scene;
	Ogre::SceneNode* node;

	std::string name;
	component_id id;

private:

	friend class Scene;
};
