#include <OgreRoot.h>
#include <OgreManualObject.h>
#include <OgreRenderWindow.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreEntity.h>

#include "Scene.h"

Scene::Scene( Ogre::Root* root, Ogre::RenderWindow* render ) : root( root ), renderWindow( render )
{
	sceneManager = root->createSceneManager( Ogre::ST_GENERIC );

	sceneManager->setAmbientLight( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );
}

ComponentLocator< GameObject > Scene::AddGameObject( const char* name )
{
	gameObjects.emplace_back( this, name );
	return ComponentLocator< GameObject >( &gameObjects, gameObjects.back().id, gameObjects.size() - 1 );
}

ComponentLocator< CameraComponent > Scene::AddCameraComponent( const GameObject& owner )
{
	// create camera and viewport
	Ogre::Camera* camera = sceneManager->createCamera( std::to_string( owner.id ) );
	owner.node->attachObject( camera );
	Ogre::Viewport* viewport = renderWindow->addViewport( camera );
	viewport->setBackgroundColour( Ogre::ColourValue( 1, 0, 0, 1 ) );

	// temporary values for testing purposes
	camera->setNearClipDistance( 5 );

	// create camera component
	cameraComponents.emplace_back( camera, viewport, LocateGameObject( owner ) );
	return ComponentLocator< CameraComponent >( &cameraComponents, cameraComponents.back().id, cameraComponents.size() - 1 );
}

void Scene::AddMeshToGameObject( GameObject* gameObject, const char* name, const char* mesh )
{
	Ogre::Entity* cubeEntity = sceneManager->createEntity( name, mesh );
	cubeEntity->setMaterialName( "Test/ColourTest" );
	gameObject->node->attachObject( cubeEntity );
}

Ogre::SceneManager* Scene::SceneManager()
{
	return sceneManager;
}

ComponentLocator< GameObject > Scene::LocateGameObject( const GameObject& gameObject )
{
	size_t index = 0;
	for ( ; index < gameObjects.size() && gameObjects[index] != gameObject; index++ );
	return ComponentLocator< GameObject >( &gameObjects, gameObject.id, index );
}
