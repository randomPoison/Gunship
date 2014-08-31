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

ComponentInfo Scene::AddGameObject()
{
	gameObjects.emplace_back( sceneManager->getRootSceneNode()->createChildSceneNode() );
	return ComponentInfo{ gameObjects.back().id, gameObjects.size() - 1 };
}

void Scene::Update( const Input& input, float delta )
{
}
