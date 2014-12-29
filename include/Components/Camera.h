#pragma once

#include <entityx/Entity.h>

#include "Components/Transform.h"

namespace Ogre
{
	class SceneManager;
	class Camera;
}

namespace Gunship
{
	class Scene;

	namespace Components
	{
		/**
		 * @brief Component representing a camera in the rendering system.
		 *
		 * @details
		 *     Each Camera component holds a reference to and Ogre::Camera object.
		 *
		 * @remark
		 *     Each camera creates a new compositor workspace in Ogre.
		 *     I don't know if this is the most appropriate way to go about things,
		 *     but at this point it works. This should be revisited once Gunship and
		 *     Ogre 2.0 are more mature.
		 */
		struct Camera : entityx::Component< Camera >
		{
			Ogre::Camera* camera;

			Camera( const Scene& scene, Components::Transform::Handle transform, const char* cameraName = "Camera" );
		};
	}
}
