#pragma once

#include <string>

// forward declarations
namespace Ogre
{
	class SceneNode;
}

class Scene;
class Camera;

class GameObjectComponent
{
public:
	GameObjectComponent( Scene* scene, Ogre::SceneNode* node, const char* name = "Game Object" );

private:
	Camera cameraComponent;

	Scene* scene;
	Ogre::SceneNode* node;

	std::string name;
	component_id id;

	friend class Scene;
};

class GameObject : public ComponentLocator
{
public:
	GameObject( Scene& scene, component_id id, size_t index = 0 );

	Camera AddCamera();
	void AddMesh( const char* name, const char* mesh );

	void LookAt( float x, float y, float z );
	void Translate( float x, float y, float z );
	void SetPosition( float x, float y, float z );

	size_t LastIndex() const;
};
