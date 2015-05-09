#include <OgreRoot.h>
#include <OgreSceneManager.h>

#include <SDL_assert.h>

#include "Scene.h"

#include "Systems/AlarmSystem.h"
#include "Systems/CollisionSystem.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Mesh.h"
#include "Components/Alarm.h"
#include "Components/Collider.h"
#include "Components/Collision.h"

namespace Gunship
{
	Scene::Scene( Engine* engine, Ogre::Root* root, Ogre::RenderWindow* render )
		: _engine( engine ),
		  _root( root ),
		  _renderWindow( render ),
		  _entities( *this )
	{
		_sceneManager = _root->createSceneManager( Ogre::ST_GENERIC,
		                                           1,
		                                           Ogre::INSTANCING_CULLING_SINGLETHREAD );
		_sceneManager->setAmbientLight( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );

		RegisterComponentManager< Components::TransformManager >( new Components::TransformManager( *this ) );
		RegisterComponentManager< Components::CameraManager >( new Components::CameraManager( *this ) );
		RegisterComponentManager< Components::MeshManager >( new Components::MeshManager( *this ) );
		RegisterComponentManager< Components::AlarmManager >( new Components::AlarmManager );
		RegisterComponentManager< Components::ColliderManager >( new Components::ColliderManager( *this ) );
		RegisterComponentManager< Components::CollisionManager >( new Components::CollisionManager );

		_coreSystems.Add< Systems::AlarmSystem >();
		_coreSystems.Add< Systems::CollisionSystem >();
	}

	Gunship::Engine& Scene::engine() const
	{
		return *_engine;
	}

	Ogre::Root& Scene::ogreRoot() const
	{
		return *_root;
	}

	Ogre::RenderWindow& Scene::renderWindow() const
	{
		return *_renderWindow;
	}

	Ogre::SceneManager& Scene::sceneManager() const
	{
		return *_sceneManager;
	}

	EntityManager& Scene::entities()
	{
		return _entities;
	}

	SystemManager< BehaviorSystemBase >& Scene::behaviors()
	{
		return _behaviorSystems;
	}

	void Scene::Update( float delta )
	{
		// Update all behaviors.
		_coreSystems.UpdateAll( *this, delta );
		_behaviorSystems.UpdateAll( *this, delta );

		// Destroy all marked components.
		for ( auto& manager : _componentManagers )
		{
			manager->DestroyAllMarked();
		}
	}

	ComponentManagerBase& Scene::_componentManager( ComponentManagerBase::ID id )
	{
		return *_componentManagers[id];
	}

	void Scene::_RegisterComponentManager( ComponentManagerBase* manager, ComponentManagerBase::ID id )
	{
		while ( _componentManagers.size() <= id )
		{
			_componentManagers.push_back( { nullptr } );
		}

		_componentManagers[id] = std::shared_ptr< ComponentManagerBase >( manager );
	}
}
