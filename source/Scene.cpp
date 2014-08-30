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
	RunCollisions();

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

void Scene::RunCollisions()
{
	// clear previous collision list
	collisions.clear();

	// run collisions
	// integer index necessary for the case where colliders.size() is 0
	for ( int first = 0; first < (int)colliders.size() - 1; first++ )
	{
		for ( unsigned second = first + 1; second < colliders.size(); second++ )
		{
			if ( ColliderComponent::Collide( colliders[first], colliders[second] ) )
			{
				collisions.emplace_back( std::make_pair( Collider( *this, colliders[first].id, first ), Collider( *this, colliders[second].id, second ) ) );
			}
		}
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
	cameraComponents.emplace_back( gameObject, camera, viewport );
	return Camera( this, cameraComponents.back().id, cameraComponents.size() - 1 );
}

Behavior Scene::AddBehaviorComponent( GameObject& gameObject, BehaviorFunction behavior )
{
	behaviorComponents.emplace_back( gameObject, behavior );
	FindComponent( gameObject )->numBehaviors++;
	return Behavior( *this, behaviorComponents.back().id, behaviorComponents.size() - 1 );
}

Collider Scene::AddColliderComponent( GameObject& gameObject, float radius )
{
	colliders.emplace_back( gameObject, radius );
	return Collider( *this, colliders.back().id, colliders.size() - 1 );
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

bool Scene::MarkForDestroy( Collider collider )
{
	if ( std::find( collidersToDestroy.begin(), collidersToDestroy.end(), collider ) == collidersToDestroy.end() )
	{
		collidersToDestroy.push_back( collider );
		return true;
	}
	return false;
}

void Scene::DestroyMarkedComponents()
{
	// ====================
	// DESTROY GAME OBJECTS
	// ====================
	for ( GameObject& gameObject : gameObjectsToDestroy )
	{
		GameObjectComponent* component = FindComponent( gameObject );

		// track down the behaviors the component owns
		for ( size_t behaviorIndex = 0, count = 0; behaviorIndex < behaviorComponents.size() && count < component->numBehaviors; behaviorIndex++ )
		{
			if ( behaviorComponents[behaviorIndex].owner.id == gameObject.id )
			{
				MarkForDestroy( Behavior( *this, behaviorComponents[behaviorIndex].id, behaviorIndex ) );
				count++;
			}
		}

		// track down the colliders the component owns
		for ( size_t colliderIndex = 0; colliderIndex < colliders.size(); colliderIndex++ )
		{
			if ( colliders[colliderIndex].owner.id == gameObject.id )
			{
				MarkForDestroy( Collider( *this, colliders[colliderIndex].id, colliderIndex ) );
				break;
			}
		}

		// retrieve the component's index from the locator,
		// the value will be accurate because we called FindComponent() earlier.
		int gameObjectIndex = gameObject.index;

		// handle destruction of component's resources
		component->node->getParent()->removeChild( component->node );

		// remove component by swapping it with last live component
		gameObjects[gameObjectIndex] = gameObjects.back();
		gameObjects.pop_back();
	}
	gameObjectsToDestroy.clear();

	// =================
	// DESTROY BEHAVIORS
	// =================
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

	// =================
	// DESTROY COLLIDERS
	// =================
	for ( Collider& collider : collidersToDestroy )
	{
		// find the component's index
		// using the same method as Scene::FindComponent()
		int colliderIndex = ( collider.index < colliders.size() ) ? collider.index : colliders.size() - 1;
		for ( ; colliderIndex >= 0 && colliders[colliderIndex].id != collider.id; colliderIndex-- );

		// destroy component by swapping it with the last live component
		colliders[colliderIndex] = colliders.back();
		colliders.pop_back();
	}
	collidersToDestroy.clear();
}
