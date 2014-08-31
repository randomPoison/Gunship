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
}

ComponentInfo Scene::AddGameObject()
{
	gameObjects.emplace_back( sceneManager->getRootSceneNode()->createChildSceneNode() );
	return ComponentInfo{ gameObjects.back().id, gameObjects.size() - 1 };
}

void Scene::AddCameraComponent( ComponentInfo& gameObject )
{
	GameObjectComponent* owner = FindGameObject( gameObject );
	Ogre::Camera* camera = sceneManager->createCamera( std::to_string( gameObject.id ) );
	owner->node->attachObject( camera );
	Ogre::Viewport* viewport = renderWindow->addViewport( camera );
	viewport->setBackgroundColour( Ogre::ColourValue( 1, 0, 0, 1 ) );

	// temporary values for testing purposes
	camera->setNearClipDistance( 5 );
}

GameObjectComponent* Scene::FindGameObject( ComponentInfo& gameObjectInfo )
{
	for ( int index = static_cast<int>( gameObjectInfo.index ); index >= 0; index-- )
	{
		if ( gameObjects[index].id == gameObjectInfo.id )
		{
			gameObjectInfo.index = index;
			return &gameObjects[index];
		}
	}

	return nullptr;
}
