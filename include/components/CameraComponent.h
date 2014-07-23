#pragma once

#include "components/Component.h"

class CameraComponent
{
public:
	CameraComponent( ComponentLocator< CameraComponent > locator );

	void Update();

private:
	COMPONENT_MEMBERS(CameraComponent)
};
