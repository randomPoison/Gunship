#pragma once

#include "components/Component.h"
#include "components/CameraComponent.h"

class GameObject
{
public:
	~GameObject() { };

protected:
	ComponentLocator< CameraComponent > cameraComponet;
};
