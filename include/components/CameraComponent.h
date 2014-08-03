#pragma once

// forward declarations
namespace Ogre
{
	class Camera;
	class Viewport;
}

class GameObject;

class CameraComponent
{
public:
	CameraComponent( Ogre::Camera* cam, Ogre::Viewport* view );

private:
	component_id id;

	Ogre::Camera* camera;
	Ogre::Viewport* viewport;

	friend class Scene;
};

class Camera : ComponentLocator
{
public:
	Camera( Scene* scene = nullptr, component_id id = 0, size_t index = 0 );
};
