#include <OgreCamera.h>
#include <OgreViewport.h>

#include "Gunship.h"

CameraComponent::CameraComponent( Ogre::Camera* cam, Ogre::Viewport* view ) :
	camera( cam ),
	viewport( view ),
	id( GenerateUniqueComponentID() )
{
}

Camera::Camera( Scene* scene, component_id id, size_t index ) : ComponentLocator( scene, id, index )
{
}
