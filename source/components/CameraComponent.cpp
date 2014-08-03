#include <OgreCamera.h>
#include <OgreViewport.h>

#include "components/Component.h"
#include "components/CameraComponent.h"
#include "GameObject.h"

CameraComponent::CameraComponent( Ogre::Camera* cam, Ogre::Viewport* view ) :
	camera( cam ),
	viewport( view ),
	id( GenerateUniqueComponentID() )
{
}

Camera::Camera( Scene* scene, component_id id, size_t index ) : ComponentLocator( scene, id, index )
{
}
