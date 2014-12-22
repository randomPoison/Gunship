#include <entityx/Event.h>

#include "Scene.h"
#include "Engine.h"

entityx::EventManager gNullEventManager; //!< Null event manager to give to the EntityManager's constructor.

Gunship::Scene::Scene( Engine* engine, Ogre::Root* root, Ogre::RenderWindow* render ) :
	_engine( engine ),
	_root( root ),
	_renderWindow( render ),
	_entities( gNullEventManager )
{
	_sceneManager = _root->createSceneManager( Ogre::ST_GENERIC,
	                                           1,
	                                           Ogre::INSTANCING_CULLING_SINGLETHREAD );
	_sceneManager->setAmbientLight( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );
}

entityx::Entity Gunship::Scene::CreateGameObject()
{
	return _entities.create();
}

Gunship::Engine& Gunship::Scene::engine() const
{
	return *_engine;
}

Ogre::Root& Gunship::Scene::ogreRoot() const
{
	return *_root;
}

Ogre::RenderWindow& Gunship::Scene::renderWindow() const
{
	return *_renderWindow;
}

Ogre::SceneManager& Gunship::Scene::sceneManager() const
{
	return *_sceneManager;
}

void Gunship::Scene::Update( float delta )
{
	_coreSystems.UpdateAll();
	_behaviorSystems.UpdateAll( _entities, delta );
}
