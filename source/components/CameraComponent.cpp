#include <OgreCamera.h>
#include <OgreViewport.h>

#include "components/CameraComponent.h"

CameraComponent::CameraComponent( Ogre::Camera* cam, Ogre::Viewport* view, ComponentLocator< GameObject > owner ) :
	camera( cam ),
	viewport( view ),
	owner( owner )
{
}

bool operator==( const CameraComponent& first, const CameraComponent& second )
{
	return first.id == second.id;
}
