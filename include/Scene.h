#pragma once

#include <vector>
#include <utility>

#include "Engine.h"

namespace Gunship
{
	class Engine;

	class Scene
	{
	public:
		Engine* _engine;

		//std::vector< GameObjectComponent > gameObjects;

		Ogre::Root* _root;
		Ogre::SceneManager* _sceneManager;
		Ogre::RenderWindow* _renderWindow;

		Scene( Engine* engine, Ogre::Root* root, Ogre::RenderWindow* renderWindow );

		void Update( const Input& input, float delta );

		// javascript helper functions
//		ComponentInfo AddGameObject( const char* name = "GameObject" );
//		void AddCameraComponent( ComponentInfo& gameObject );
//		void AddMesh( ComponentInfo& gameObject, const char* mesh );
//
//		GameObjectComponent* FindGameObject( ComponentInfo& gameObjectInfo );
	};
}
