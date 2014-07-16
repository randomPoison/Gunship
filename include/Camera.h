#pragma once

#include "Component.h"
#include "GameObject.h"

class CameraComponent
{
public:
	CameraComponent();
	COMPONENT_MEMBERS(CameraComponent)
};

DEFINE_COMPONENT(CameraComponent)

void CameraComponent::Update()
{
	// do cool things
}

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
