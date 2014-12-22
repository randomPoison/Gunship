#include "Engine.h"
#include "Scene.h"
#include "System.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Mesh.h"
#include "Components/Light.h"

struct Player : public entityx::Component< Player >
{
	Player( float speed = 1.0f )
		: moveSpeed( speed )
	{
	}

	float moveSpeed;
};

struct PlayerMovementSystem : public Gunship::System< PlayerMovementSystem, Gunship::BehaviorSystemBase >
{
	void Update( entityx::EntityManager& entities,
	             float delta ) override
	{
		Gunship::Transform::Handle transform;
		Player::Handle player;
		for ( entityx::Entity entity : entities.entities_with_components( transform, player ) )
		{
			transform->node->translate( player->moveSpeed * delta, 0.0f, 0.0f );
		}
	}
};

void InitializeScene( Gunship::Scene& scene )
{
	// add systems to scene
	scene.AddSystem< PlayerMovementSystem >();

	entityx::Entity camera = scene.CreateGameObject();
	Gunship::Transform::Handle cameraTransform = camera.assign<
		Gunship::Transform >( scene );
	camera.assign< Gunship::Camera >( scene, cameraTransform );
	cameraTransform->node->setPosition( 20.0f, 15.0f, 30.0f );
	cameraTransform->node->_getDerivedPositionUpdated(); // trigger ogre to recalculate derived position.
	cameraTransform->node->lookAt( Ogre::Vector3( 0.0f, 0.0f, 0.0f ),
	                               Ogre::Node::TS_WORLD );

	entityx::Entity cube = scene.CreateGameObject();
	Gunship::Transform::Handle cubeTransform =
		cube.assign< Gunship::Transform >( scene );
	cube.assign< Gunship::Mesh >( scene, cubeTransform, "Cube.mesh" );
	cube.assign< Player >( 2.0f );

	entityx::Entity light = scene.CreateGameObject();
	Gunship::Transform::Handle lightTransform =
		light.assign< Gunship::Transform >( scene );
	lightTransform->node->setPosition( 12.0f, 56.0f, 3.0f );
	light.assign< Gunship::Components::Light >( scene, lightTransform );
}

int main( int argc, char* argv[] )
{
	Gunship::Engine engine;

	// initialize and run the engine
	if ( engine.InitSystems() )
	{
		engine.SetupCurrentScene( InitializeScene );
		engine.Start();
		engine.ShutDown();
	}

	return 0;
}
