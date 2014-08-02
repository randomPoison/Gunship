#pragma once

// forward declarations
namespace Ogre
{
	class Camera;
	class Viewport;
}

#include "components/Component.h"

class CameraComponent
{
public:
	CameraComponent( Ogre::Camera* cam, Ogre::Viewport* view, ComponentLocator< GameObject > owner );

private:
	ComponentLocator< GameObject > owner;
	component_id id;

	Ogre::Camera* camera;
	Ogre::Viewport* viewport;

	friend class Scene;
	friend bool operator==( const CameraComponent& first, const CameraComponent& second );
};

bool operator==( const CameraComponent& first, const CameraComponent& second );
