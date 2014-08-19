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

void Scene::Update( const Input& input, float delta )
{
	// cache original number of components
	// in case new ones are added during frame
	size_t numBehaviors = behaviorComponents.size();
	for ( size_t index = 0; index < numBehaviors; index++ )
	{
		BehaviorComponent& behavior = behaviorComponents[index];
		behavior.behavior( behavior.owner, *this ,input, delta );
	}

	// remove any game objects that need to be destroyed
	DestroyMarkedComponents();
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
	FindComponent( gameObject )->numBehaviors++;
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
	for ( int index = ( gameObject.index < gameObjects.size() ) ? gameObject.index : gameObjects.size() - 1; index >= 0; index-- )
	{
		GameObjectComponent& component = gameObjects[index];
		if ( component.id == gameObject.id )
		{
			// update cached index
			gameObject.index = index;
			return &component;
		}
	}
	return nullptr;
}

bool Scene::MarkForDestroy( GameObject gameObject )
{
	if ( std::find( gameObjectsToDestroy.begin(), gameObjectsToDestroy.end(), gameObject ) == gameObjectsToDestroy.end() )
	{
		gameObjectsToDestroy.push_back( gameObject );
		return true;
	}
	return false;
}

bool Scene::MarkForDestroy( Behavior behavior )
{
	if ( std::find( behaviorsToDestroy.begin(), behaviorsToDestroy.end(), behavior ) == behaviorsToDestroy.end() )
	{
		behaviorsToDestroy.push_back( behavior );
		return true;
	}
	return false;
}

void Scene::DestroyMarkedComponents()
{
	// DESTROY GAME OBJECTS
	for ( GameObject& gameObject : gameObjectsToDestroy )
	{
		GameObjectComponent* component = FindComponent( gameObject );

		// track down the behaviors the components owns
		// and mark them for destruction
		for ( size_t count = 0; count < component->numBehaviors; count++ )
		{
			for ( size_t behaviorIndex = 0; behaviorIndex < behaviorComponents.size(); behaviorIndex++ )
			{
				if ( behaviorComponents[behaviorIndex].owner.id == gameObject.id )
				{
					MarkForDestroy( Behavior( *this, behaviorComponents[behaviorIndex].id, behaviorIndex ) );
				}
			}
		}

		// find the component's index
		int gameObjectIndex = ( gameObject.index < gameObjects.size() ) ? gameObject.index : gameObjects.size() - 1;
		for ( ; gameObjectIndex >= 0 && gameObjects[gameObjectIndex].id != gameObject.id; gameObjectIndex-- );

		// handle destruction of component's resources
		component->node->getParent()->removeChild( component->node );

		// remove component by swapping it with last live component
		gameObjects[gameObjectIndex] = gameObjects.back();
		gameObjects.pop_back();
	}
	gameObjectsToDestroy.clear();

	// DESTROY BEHAVIORS
	for ( Behavior& behavior : behaviorsToDestroy )
	{
		// find the component's index
		// using the same method as Scene::FindComponent()
		int behaviorIndex = ( behavior.index < behaviorComponents.size() ) ? behavior.index : behaviorComponents.size() - 1;
		for ( ; behaviorIndex >= 0 && behaviorComponents[behaviorIndex].id != behavior.id; behaviorIndex-- );

		// destroy component by swapping it with last live component
		behaviorComponents[behaviorIndex] = behaviorComponents.back();
		behaviorComponents.pop_back();
	}
	behaviorsToDestroy.clear();
}
