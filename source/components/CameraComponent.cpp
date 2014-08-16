#include "Gunship.h"
#include "components/CameraComponent.h"

CameraComponent::CameraComponent( Ogre::Camera* cam, Ogre::Viewport* view ) :
	id( GenerateUniqueComponentID() ),
	camera( cam ),
	viewport( view )
{
}

Camera::Camera( Scene* scene, component_id id ) : ComponentLocator( scene, id )
{
}
