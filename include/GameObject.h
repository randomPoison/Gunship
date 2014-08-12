#pragma once

#include <string>

// forward declarations
namespace Ogre
{
	class SceneNode;
	class Vector3;
}

class Scene;
class Camera;

class GameObjectComponent
{
public:
	GameObjectComponent( Scene* scene, Ogre::SceneNode* node, const char* name = "Game Object" );

	Camera cameraComponent;

	Scene* scene;
	Ogre::SceneNode* node;

	std::string name;
	component_id id;
};

class GameObject final : public ComponentLocator
{
public:
	GameObject( Scene* scene = nullptr, component_id id = 0, size_t index = 0 );

	Camera AddCamera();
	void AddMesh( const char* name, const char* mesh );
	Behavior AddBehavior( BehaviorFunction behavior );

	void LookAt( float x, float y, float z );
	void LookAt( GameObject& target );
	void Translate( float x, float y, float z );
	void SetPosition( float x, float y, float z );
	void SetScale( float x, float y, float z );

	Ogre::Vector3 Position();

	void AddChild( GameObject& gameObject );

	size_t LastIndex() const;
};
