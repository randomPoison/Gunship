#include <entityx/Event.h>

#include "Scene.h"
#include "Engine.h"

namespace Gunship
{
	entityx::EventManager gNullEventManager; //!< Null event manager to give to the EntityManager's constructor.

	Scene::Scene( Engine* engine, Ogre::Root* root, Ogre::RenderWindow* render )
		: _engine( engine ),
		  _root( root ),
		  _renderWindow( render ),
		  _entities( gNullEventManager )
	{
		_sceneManager = _root->createSceneManager( Ogre::ST_GENERIC,
		                                           1,
		                                           Ogre::INSTANCING_CULLING_SINGLETHREAD );
		_sceneManager->setAmbientLight( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );
	}

	entityx::Entity Scene::CreateGameObject()
	{
		return _entities.create();
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

	entityx::EntityManager& Scene::entities()
	{
		return _entities;
	}

	void Gunship::Scene::Update( float delta )
	{
		_coreSystems.UpdateAll( *this );
		_behaviorSystems.UpdateAll( *this, delta );
	}
}
