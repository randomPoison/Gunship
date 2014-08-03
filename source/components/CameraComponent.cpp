#include <OgreCamera.h>
#include <OgreViewport.h>

#include "components/Component.h"
#include "components/CameraComponent.h"
#include "GameObject.h"

CameraComponent::CameraComponent( Ogre::Camera* cam, Ogre::Viewport* view, GameObject owner ) :
	camera( cam ),
	viewport( view ),
	owner( owner ),
	id( GenerateUniqueComponentID() )
{
}

bool operator==( const CameraComponent& first, const CameraComponent& second )
{
	return first.id == second.id;
}
