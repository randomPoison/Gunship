#pragma once

#include <vector>

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
};

class Scene
{
public:
	Scene( Ogre::Root* root, Ogre::RenderWindow* renderWindow );

	GameObject AddGameObject( const char* name = "Game Object" );
	ComponentLocator< CameraComponent > AddCameraComponent( GameObject gameObject );

	void AddMeshToGameObject( GameObject gameObject, const char* name, const char* mesh );
	void TranslateGameObject( GameObject gameObject, float x, float y, float z );
	void SetGameObjectPosition( GameObject gameObject, float x, float y, float z );
	void SetGameObjectLook( GameObject gameObject, float x, float y, float z );

private:
	std::vector< GameObjectComponent > gameObjects;
	std::vector< CameraComponent > cameraComponents;

	Ogre::Root* root;
	Ogre::SceneManager* sceneManager;
	Ogre::RenderWindow* renderWindow;

	GameObjectComponent* FindComponent( GameObject gameObject );
	CameraComponent* FindComponent( ComponentLocator< CameraComponent > camera );
};
