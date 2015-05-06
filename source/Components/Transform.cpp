#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include "Components/Transform.h"
#include "Scene.h"

namespace Gunship
{
	namespace Components
	{
		Vector3 Transform::position()
		{
			return node->getPosition();
		}

		void Transform::position( float x, float y, float z )
		{
			node->setPosition( x, y, z );
		}

		void Transform::position( Vector3 position )
		{
			node->setPosition( position );
		}

		Vector3 Transform::derivedPosition()
		{
			return node->_getDerivedPositionUpdated();
		}

		void Transform::derivedPosition( float x, float y, float z )
		{
			node->_setDerivedPosition( Vector3( x, y, z ) );
		}

		void Transform::derivedPosition( Vector3 position )
		{
			node->_setDerivedPosition( position );
		}


		void Transform::Translate( float x, float y, float z )
		{
			node->translate( x, y, z, Ogre::Node::TS_LOCAL );
		}

		void Transform::Translate( Vector3 translation )
		{
			node->translate( translation, Ogre::Node::TS_LOCAL );
		}

		void Transform::TranslateWorld( float x, float y, float z )
		{
			node->translate( x, y, z, Ogre::Node::TS_WORLD );
		}

		void Transform::TranslateWorld( Vector3 translation )
		{
			node->translate( translation, Ogre::Node::TS_WORLD );
		}


		void Transform::LookAt( float x, float y, float z )
		{
			node->lookAt( Vector3( x, y, z ), Ogre::Node::TS_LOCAL );
		}

		void Transform::LookAt( Vector3 target )
		{
			node->lookAt( target, Ogre::Node::TS_LOCAL );
		}

		void Transform::LookAtWorld( float x, float y, float z )
		{
			node->_getDerivedPositionUpdated();
			node->lookAt( Vector3( x, y, z ), Ogre::Node::TS_WORLD );
		}

		void Transform::LookAtWorld( Vector3 target )
		{
			node->_getDerivedPositionUpdated();
			node->lookAt( target, Ogre::Node::TS_WORLD );
		}


		void Transform::SetPosition( float x, float y, float z )
		{
			position( x, y , z );
		}

		void Transform::SetPosition( Vector3 position )
		{
			this->position( position );
		}

		void Transform::SetDerivedPosition( float x, float y, float z )
		{
			derivedPosition( x, y, z );
		}

		void Transform::SetDerivedPosition( Vector3 position )
		{
			derivedPosition( position );
		}


		void Transform::SetScale( float x, float y, float z )
		{
			node->setScale( x, y, z );
		}

		void Transform::SetScale( Vector3 scale )
		{
			node->setScale( scale );
		}


		void Transform::AddChild( Transform* child )
		{
			// make sure new node isn't already a child of another node
			if ( child->node->getParentSceneNode() != nullptr )
			{
				child->node->getParentSceneNode()->removeChild( child->node );
			}

			node->addChild( child->node );
		}

		void Transform::RemoveChild( Transform* child )
		{
			node->removeChild( child->node );
		}

		void Transform::RemoveAllChildren()
		{
			node->removeAllChildren();
		}

		TransformManager::TransformManager( Scene& scene )
			: _scene( scene )
		{
		}

		void TransformManager::Disable( Transform& transform )
		{
			transform.node->detachAllObjects();

			// Move node back to root if it's not already there.
			Ogre::SceneNode* rootNode = _scene.sceneManager().getRootSceneNode();
			if ( transform.node->getParentSceneNode() != rootNode )
			{
				transform.node->getParentSceneNode()->removeChild( transform.node );
				rootNode->addChild( transform.node );
			}
		}

		void TransformManager::Enable( Entity::ID entityID, Transform& transform )
		{
			//_scene.sceneManager().getRootSceneNode()->addChild( transform.node );
		}

		Transform TransformManager::Construct( Entity::ID entityID )
		{
			Transform transform;
			transform.node = _scene.sceneManager().createSceneNode();
			_scene.sceneManager().getRootSceneNode()->addChild( transform.node );
			return transform;
		}

		void TransformManager::Destruct( Transform& transform )
		{
			transform.node->getCreator()->destroySceneNode( transform.node );
		}
	}
}
