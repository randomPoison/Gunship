#pragma once

#include <entityx/Entity.h>

#include "Math/Vector3.h"
#include "Math/Quaternion.h"

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
		Ogre::SceneNode* node;

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
		           Vector3 position       = Vector3::ZERO,
		           Quaternion orientation = Quaternion::IDENTITY,
		           Vector3 scale          = Vector3::UNIT_SCALE );

		Vector3 position();
		void position( float x, float y, float z );
		void position( Vector3 position );
		Vector3 derivedPosition();
		void derivedPosition( float x, float y, float z );
		void derivedPosition( Vector3 position );
		void derivedPosition_Updated();

		void Translate( float x, float y, float z );
		void Translate( Vector3 translation );
		void TranslateWorld( float x, float y, float z );
		void TranslateWorld( Vector3 translation );

		void SetPosition( float x, float y, float z );
		void SetPosition( Vector3 position );
		void SetDerivedPosition( float x, float y, float z );
		void SetDerivedPosition( Vector3 position );

		void SetScale( float x, float y, float z );
		void SetScale( Vector3 scale );
	};
}
