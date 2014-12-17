#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include "Components/Transform.h"
#include "Scene.h"

Gunship::Transform::Transform( const Scene& scene,
                               Ogre::Vector3 position,
                               Ogre::Quaternion orientation,
                               Ogre::Vector3 scale )
	: node( nullptr )
{
	Ogre::SceneManager& sceneManager = scene.sceneManager();
	node = sceneManager.createSceneNode();
	sceneManager.getRootSceneNode()->addChild( node );
	node->setPosition( position );
	node->setOrientation( orientation );
	node->setScale( scale );
}
