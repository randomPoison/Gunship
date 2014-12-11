#include "Scene.h"
#include "Engine.h"

Gunship::Scene::Scene( Engine* engine, Ogre::Root* root, Ogre::RenderWindow* render ) :
	_engine( engine ),
	_root( root ),
	_renderWindow( render )
{
	_sceneManager = _root->createSceneManager( Ogre::ST_GENERIC,
	                                           1,
	                                           Ogre::INSTANCING_CULLING_SINGLETHREAD );
	_sceneManager->setAmbientLight( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );

	/// @TODO Initialize all systems.
}

void Gunship::Scene::Update( const Input& input, float delta )
{
	/// @TODO Update all systems.
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
