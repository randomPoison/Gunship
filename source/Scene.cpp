#include "Gunship.h"
#include "Scene.h"

static std::string MeshID( const char* name, GameObjectComponent* owner )
{
	return std::string( name ) + std::to_string( owner->id );
}

Scene::Scene( Ogre::Root* root, Ogre::RenderWindow* render ) : root( root ), renderWindow( render )
{
	sceneManager = root->createSceneManager( Ogre::ST_GENERIC );

	sceneManager->setAmbientLight( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );
}

void Scene::Update( const Input& input )
{
	// cache original number of components
	// in case new ones are added during frame
	size_t numBehaviors = behaviorComponents.size();
	for ( size_t index = 0; index < numBehaviors; index++ )
	{
		BehaviorComponent& behavior = behaviorComponents[index];
		GameObject obj( this, FindComponent( behavior.owner )->node, behavior.owner.id, 0 );
		behavior.behavior( obj, *this ,input );
	}
}

GameObject Scene::AddGameObject( const char* name )
{
	gameObjects.emplace_back( this, sceneManager->getRootSceneNode()->createChildSceneNode(), name );
	return GameObject( this, gameObjects.back().node, gameObjects.back().id, gameObjects.size() - 1 );
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
	Ogre::Entity* cubeEntity = sceneManager->createEntity( MeshID( name, owner ).c_str(), mesh );
	cubeEntity->setMaterialName( "Test/ColourTest" );
	owner->node->attachObject( cubeEntity );
}

GameObjectComponent* Scene::FindComponent( GameObject& gameObject )
{
	// game objects can only ever be moved backwards,
	// so start at last known index and search back.
	for ( size_t index = gameObject.index; index >= 0; index-- )
	{
		GameObjectComponent& component = gameObjects[index];
		if ( component.id = gameObject.id )
		{
			return &component;
		}
	}
	return nullptr;
}
