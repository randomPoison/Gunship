#pragma once

#include <vector>

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
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

public:
	Scene( Ogre::Root* root, Ogre::RenderWindow* renderWindow );

	ComponentLocator< GameObject > AddGameObject( const char* name = "Game Object" );

	Ogre::SceneManager* SceneManager();
};
