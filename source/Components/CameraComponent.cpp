#include "Gunship.h"
#include "Components/CameraComponent.h"

CameraComponent::CameraComponent(  GameObject& owner, Ogre::Camera* cam, Ogre::Viewport* view ) :
	Component( owner ),
	camera( cam ),
	viewport( view )
{
}
