#pragma once

#include <vector>

#include "GameObject.h"

namespace Ogre {
	class Root;
	class RenderWindow;
};

#include "GameObject.h"
#include "components/Component.h"

class Scene
{
private:
	std::vector< GameObject > gameObjects;

	Ogre::Root* root;
	Ogre::SceneManager* sceneManager;
	Ogre::RenderWindow* renderWindow;
	Ogre::Camera* camera;
	Ogre::Viewport* viewport;

public:
	Scene( Ogre::Root* root, Ogre::RenderWindow* renderWindow );

	ComponentLocator< GameObject > AddGameObject();
};
