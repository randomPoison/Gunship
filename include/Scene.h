#pragma once

#include <vector>
#include <utility>

class Scene
{
public:
	Scene( Ogre::Root* root, Ogre::RenderWindow* renderWindow );

	// javascript helper functions
	ComponentInfo AddGameObject();
	ComponentInfo AddCameraComponent( const v8::FunctionCallbackInfo< v8::Value >& args );

private:
	std::vector< GameObjectComponent > gameObjects;

	Ogre::Root* root;
	Ogre::SceneManager* sceneManager;
	Ogre::RenderWindow* renderWindow;

	void Update( const Input& input, float delta );
	void RunCollisions();
	void DestroyMarkedComponents();

	friend class Gunship;
	friend class ComponentLocator;
};
