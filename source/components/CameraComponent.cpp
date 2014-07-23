#include "components/CameraComponent.h"

CameraComponent::CameraComponent( ComponentLocator<CameraComponent> locator )
{
	this->locator = locator;
	// setup the component
}

void CameraComponent::Update()
{
	// do cool things
}
