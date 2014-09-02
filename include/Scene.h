#pragma once

#include <vector>
#include <utility>

class Scene
{
public:
	std::vector< GameObjectComponent > gameObjects;
	std::vector< BehaviorComponent > behaviors;

	Ogre::Root* root;
	Ogre::SceneManager* sceneManager;
	Ogre::RenderWindow* renderWindow;

	Scene( Ogre::Root* root, Ogre::RenderWindow* renderWindow );

	void Update( const Input& input, float delta );

	// javascript helper functions
	ComponentInfo AddGameObject( const char* name = "GameObject" );
	void AddCameraComponent( ComponentInfo& gameObject );
	void AddMesh( ComponentInfo& gameObject, const char* mesh );
	void AddBehavior( v8::Persistent< v8::Object, v8::CopyablePersistentTraits< v8::Object > > object, v8::Persistent< v8::Function, v8::CopyablePersistentTraits< v8::Function > > function );

	GameObjectComponent* FindGameObject( ComponentInfo& gameObjectInfo );
};
