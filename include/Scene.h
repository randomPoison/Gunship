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
	std::vector< CameraComponent > cameraComponents;

	Ogre::Root* root;
	Ogre::SceneManager* sceneManager;
	Ogre::RenderWindow* renderWindow;

public:
	Scene( Ogre::Root* root, Ogre::RenderWindow* renderWindow );

	ComponentLocator< GameObject > AddGameObject( const char* name = "Game Object" );
	ComponentLocator< CameraComponent > AddCameraComponent( const GameObject& owner );

	Ogre::SceneManager* SceneManager();
	ComponentLocator< GameObject > LocateGameObject( const GameObject& gameObject );
};
