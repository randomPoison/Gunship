#pragma once

#include <entityx/Entity.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>

namespace Ogre
{
	class SceneNode;
}

namespace Gunship
{
	class Scene;

	/**
	 * @brief Component for representing the position, rotation, and scale of an object.
	 *
	 * @details
	 *    The Transform component contains the local position, rotation,
	 *    and scale, and allows retrieval of the transform in world-space.
	 *
	 * @remark
	 *     This component wraps a reference to an Ogre::SceneNode since
	 *     we let Ogre manage the scene graph for us at this point.
	 *     This may change as things go forward.
	 */
	struct Transform : public entityx::Component< Transform >
	{
		/**
		 * @brief Constructs a transform component.
		 *
		 * @param scene
		 *     The scene in which this transform is active. Note: We
		 *     should eventually be able to remove the need to explicitly
		 *     pass in the scene, since you have to go through the scene
		 *     to create the component in the first place.
		 *
		 * @param position
		 *     The position of the transform. Defaults to zero (object
		 *     is at local origin).
		 *
		 * @param orientation
		 *     The starting orientation of the transform. Defaults to
		 *     identity (no rotation).
		 *
		 * @param scale
		 *     The starting scale of the transform. Defaults to no scale.
		 */
		Transform( const Scene& scene,
		           Ogre::Vector3 position       = Ogre::Vector3::ZERO,
		           Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY,
		           Ogre::Vector3 scale          = Ogre::Vector3::UNIT_SCALE );

		Ogre::SceneNode* node;
	};
}
