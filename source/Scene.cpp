#include <OgreRoot.h>
#include <OgreManualObject.h>
#include <OgreRenderWindow.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreEntity.h>

#include "components/Component.h"
#include "components/CameraComponent.h"
#include "components/BehaviorComponent.h"
#include "GameObject.h"

#include "Scene.h"

Scene::Scene( Ogre::Root* root, Ogre::RenderWindow* render ) : root( root ), renderWindow( render )
{
	sceneManager = root->createSceneManager( Ogre::ST_GENERIC );

	sceneManager->setAmbientLight( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );
}

void Scene::Update()
{
	for ( BehaviorComponent& behavior : behaviorComponents )
	{
		GameObject obj( *this, behavior.ownerId, 0 );
		behavior.behavior( obj );
	}
}

GameObject Scene::AddGameObject( const char* name )
{
	gameObjects.emplace_back( this, sceneManager->getRootSceneNode()->createChildSceneNode(), name );
	return GameObject( *this, gameObjects.back().id, gameObjects.size() - 1 );
}

Camera Scene::AddCameraComponent( GameObject& gameObject )
{
	// create camera and viewport
	GameObjectComponent* owner = FindComponent( gameObject );
	Ogre::Camera* camera = sceneManager->createCamera( std::to_string( owner->id ) );
	owner->node->attachObject( camera );
	Ogre::Viewport* viewport = renderWindow->addViewport( camera );
	viewport->setBackgroundColour( Ogre::ColourValue( 1, 0, 0, 1 ) );

	// temporary values for testing purposes
	camera->setNearClipDistance( 5 );

	// create camera component
	cameraComponents.emplace_back( camera, viewport );
	return Camera( this, cameraComponents.back().id, cameraComponents.size() - 1 );
}

Behavior Scene::AddBehaviorComponent( GameObject& gameObject, BehaviorFunction behavior )
{
	behaviorComponents.emplace_back( gameObject, behavior );
	return Behavior( *this, behaviorComponents.back().id, behaviorComponents.size() - 1 );
}

void Scene::AddMeshToGameObject( GameObject& gameObject, const char* name, const char* mesh )
{
	GameObjectComponent* owner = FindComponent( gameObject );
	Ogre::Entity* cubeEntity = sceneManager->createEntity( name, mesh );
	cubeEntity->setMaterialName( "Test/ColourTest" );
	owner->node->attachObject( cubeEntity );
}

void Scene::TranslateGameObject( GameObject& gameObject, float x, float y, float z )
{
	GameObjectComponent* obj = FindComponent( gameObject );
	obj->node->translate( x, y, z );
}

void Scene::SetGameObjectPosition( GameObject& gameObject, float x, float y, float z )
{
	GameObjectComponent* component = FindComponent( gameObject );
	component->node->setPosition( x, y, z );
}

GameObjectComponent* Scene::FindComponent( GameObject& gameObject )
{
	return gameObjects.data() + gameObject.LastIndex();
}
