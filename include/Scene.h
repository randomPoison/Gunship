#pragma once

#include <vector>
#include <utility>

class Scene
{
public:
	Scene( Ogre::Root* root, Ogre::RenderWindow* renderWindow );

	GameObject AddGameObject( const char* name = "Game Object" );
	Camera AddCameraComponent( GameObject& gameObject );
	Behavior AddBehaviorComponent( GameObject& gameObject, BehaviorFunction behavior );
	Collider AddColliderComponent( GameObject& gameObject, float radius );

	void AddMeshToGameObject( GameObject& gameObject, const char* name, const char* mesh );
	void SetGameObjectLook( GameObject& gameObject, float x, float y, float z );

	GameObjectComponent* FindComponent( GameObject& gameObject );
	CameraComponent* FindComponent( Camera& camera );

	/**
	 * \brief Marks a game object for destruction.
	 *
	 * \param gameObject the GameObject to be marked for destruction.
	 *
	 * \returns True if the GameObject was marked, false if it had already been marked.
	 */
	bool MarkForDestroy( GameObject gameObject );

	/**
	 * \brief Marks a behavior for destruction.
	 *
	 * \param behavior the Behavior to be marked for destruction.
	 *
	 * \returns True if the Behavior was marked, false if it had already been marked.
	 */
	bool MarkForDestroy( Behavior behavior );

private:
	std::vector< GameObjectComponent > gameObjects;
	std::vector< CameraComponent > cameraComponents;
	std::vector< BehaviorComponent > behaviorComponents;
	std::vector< ColliderComponent > colliders;

	std::vector< GameObject > gameObjectsToDestroy;
	std::vector< Camera > camerasToDestroy;
	std::vector< Behavior > behaviorsToDestroy;
	std::vector< ColliderComponent > collidersToDestroy;

	std::vector< std::pair< Collider, Collider > > collisions;

	Ogre::Root* root;
	Ogre::SceneManager* sceneManager;
	Ogre::RenderWindow* renderWindow;

	void Update( const Input& input, float delta );
	void RunCollisions();
	void DestroyMarkedComponents();

	friend class Gunship;
	friend class ComponentLocator;
};
