#pragma once

// forward declarations
namespace Ogre
{
	class Camera;
	class Viewport;
}

#include "GameObject.h" // TODO figure out if there's a way to not have this here

class CameraComponent
{
public:
	CameraComponent( Ogre::Camera* cam, Ogre::Viewport* view, GameObject owner );

private:
	GameObject owner;
	component_id id;

	Ogre::Camera* camera;
	Ogre::Viewport* viewport;

	friend class Scene;
	friend bool operator==( const CameraComponent& first, const CameraComponent& second );
};

bool operator==( const CameraComponent& first, const CameraComponent& second );
