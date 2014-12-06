#pragma once

#include <entityx/Entity.h>
#include <OgreVector3.h>

namespace Gunship
{
	struct Transform : public entityx::Component< Transform >
	{
		Transform( Ogre::Vector3 position = Ogre::Vector3::ZERO,
		           Ogre::Vector3 rotation = Ogre::Vector3::ZERO,
		           Ogre::Vector3 scale    = Ogre::Vector3::ZERO );

		Ogre::Vector3 position;
		Ogre::Vector3 rotation;
		Ogre::Vector3 scale;
	};
}
