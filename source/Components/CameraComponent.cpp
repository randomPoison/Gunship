#include "Gunship.h"
#include "Components/CameraComponent.h"

CameraComponent::CameraComponent( Ogre::Camera* cam, Ogre::Viewport* view ) :
	id( GenerateUniqueComponentID() ),
	camera( cam ),
	viewport( view )
{
}

Camera::Camera( Scene* scene, component_id id, size_t index ) : ComponentLocator( scene, id, index )
{
}
