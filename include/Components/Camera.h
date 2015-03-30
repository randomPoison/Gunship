#pragma once

#include "Components/SimpleStructComponent.h"
#include "Components/SimpleStructComponentManager.h"

namespace Ogre
{
	class Camera;
}

namespace Gunship
{
	class Scene;

	namespace Components
	{
		struct Transform;

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
		struct Camera : public SimpleStructComponent
		{
			Ogre::Camera* camera;

			Camera( const Scene& scene, Transform& transform, const char* cameraName = "Camera" );
		};

		class CameraManager : public SimpleStructComponentManager< Camera >
		{
		public:
			CameraManager( Scene& scene );

			Camera& Assign( Entity::ID entity );

		private:
			Scene& _scene;

			using SimpleStructComponentManager< Camera >::Assign;
		};
	}
}
