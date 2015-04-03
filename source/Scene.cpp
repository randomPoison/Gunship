#include <OgreRoot.h>
#include <OgreSceneManager.h>

#include <SDL_assert.h>

#include "Scene.h"

#include "Systems/AlarmSystem.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Mesh.h"
#include "Components/Alarm.h"

namespace Gunship
{
	Scene::Scene( Engine* engine, Ogre::Root* root, Ogre::RenderWindow* render )
		: _engine( engine ),
		  _root( root ),
		  _renderWindow( render ),
		  _entities()
	{
		_sceneManager = _root->createSceneManager( Ogre::ST_GENERIC,
		                                           1,
		                                           Ogre::INSTANCING_CULLING_SINGLETHREAD );
		_sceneManager->setAmbientLight( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );

		RegisterComponentManager< Components::TransformManager >( new Components::TransformManager( *this ) );
		RegisterComponentManager< Components::CameraManager >( new Components::CameraManager( *this ) );
		RegisterComponentManager< Components::MeshManager >( new Components::MeshManager( *this ) );
		RegisterComponentManager< Components::AlarmManager >( new Components::AlarmManager() );

		_coreSystems.Add< Systems::AlarmSystem >();
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

	void Scene::Update( float delta )
	{
		// Update all behaviors.
		_coreSystems.UpdateAll( *this, delta );
		_behaviorSystems.UpdateAll( *this, delta );

		// Destroy all marked components.
		for ( auto& element : _componentManagers )
		{
			element.second->DestroyAllMarked();
		}
	}

	ComponentManagerBase& Scene::_componentManager( ComponentManagerBase::ID family )
	{
		SDL_assert_paranoid( _componentManagers.count( family ) );

		return *_componentManagers[family];
	}
}
