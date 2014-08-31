#pragma once

#include <vector>
#include <utility>

class Scene
{
public:
	std::vector< GameObjectComponent > gameObjects;

	Ogre::Root* root;
	Ogre::SceneManager* sceneManager;
	Ogre::RenderWindow* renderWindow;

	Scene( Ogre::Root* root, Ogre::RenderWindow* renderWindow );

	void Update( const Input& input, float delta );

	// javascript helper functions
	ComponentInfo AddGameObject();
	void AddCameraComponent( ComponentInfo& gameObject );

	GameObjectComponent* FindGameObject( ComponentInfo& gameObjectInfo );
};
