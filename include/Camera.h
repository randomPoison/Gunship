#pragma once

#include "Component.h"
#include "GameObject.h"

class CameraComponent
{
private:
	COMPONENT_MEMBERS(CameraComponent)

public:
	CameraComponent();
};

class Camera : public GameObject
{
private:
	ADD_COMPONENT(CameraComponent)

public:
	Camera()
	{
		INITIALIZE_COMPONENT(CameraComponent);
	}

	virtual ~Camera()
	{
		DESTROY_COMPONENT(CameraComponent);
	}
};
