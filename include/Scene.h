#pragma once

#include <vector>

namespace Ogre {
	class Root;
	class RenderWindow;
};

#include "GameObject.h"

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
};
