#pragma once

#include <entityx/Entity.h>

#include "Components/Transform.h"

namespace Ogre
{
	class Entity;
}

namespace Gunship
{
	class Scene;

	struct Mesh : entityx::Component< Mesh >
	{
		Mesh( const Scene& scene, const Transform::Handle& transform, const char* meshName );

		Ogre::Entity* entity;
	};
}
