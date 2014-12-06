/*
 * \file Transform.cpp
 *
 * \date Dec 6, 2014
 * \author excaliburhissheath
 */

#include "Components/Transform.h"

Gunship::Transform::Transform( Ogre::Vector3 position, Ogre::Vector3 rotation, Ogre::Vector3 scale ) :
	position( position ),
	rotation( rotation ),
	scale( scale )
{
}
