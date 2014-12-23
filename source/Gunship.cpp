#include "Engine.h"
#include "Scene.h"
#include "System.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Mesh.h"
#include "Components/Light.h"

struct Player : public entityx::Component< Player >
{
	float moveSpeed;

	Player( float speed = 1.0f )
		: moveSpeed( speed )
	{
	}
};

struct FollowTarget : public entityx::Component< FollowTarget >
{
	Gunship::Transform::Handle targetTransform;
	Ogre::Vector3 offset;
	float followSpeed;

	FollowTarget( Gunship::Transform::Handle target,
	              Ogre::Vector3 offset = Ogre::Vector3::ZERO,
	              float followSpeed = 10.0f )
		: targetTransform( target ),
		  offset( offset ),
		  followSpeed( followSpeed )
	{
	}

	Ogre::Vector3 desiredPosition()
	{
		return targetTransform->node->_getDerivedPosition() + offset;
	}
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
			if ( Gunship::Input::KeyDown( SDL_SCANCODE_D ) )
			{
				transform->node->translate( Ogre::Vector3::UNIT_X * player->moveSpeed * delta );
			}
			if ( Gunship::Input::KeyDown( SDL_SCANCODE_A ) )
			{
				transform->node->translate( Ogre::Vector3::NEGATIVE_UNIT_X * player->moveSpeed * delta );
			}
			if ( Gunship::Input::KeyDown( SDL_SCANCODE_W ) )
			{
				transform->node->translate( Ogre::Vector3::UNIT_Y * player->moveSpeed * delta );
			}
			if ( Gunship::Input::KeyDown( SDL_SCANCODE_S ) )
			{
				transform->node->translate( Ogre::Vector3::NEGATIVE_UNIT_Y * player->moveSpeed * delta );
			}

			transform->node->_getDerivedPositionUpdated();
		}
	}
};

struct CameraFollowSystem : public Gunship::System< CameraFollowSystem, Gunship::BehaviorSystemBase >
{
	void Update( entityx::EntityManager& entities,
	             float delta ) override
	{
		FollowTarget::Handle followTarget;
		Gunship::Transform::Handle transform;
		for ( entityx::Entity entity : entities.entities_with_components( followTarget, transform ) )
		{
			Ogre::Vector3 desiredPostition = followTarget->desiredPosition();
			Ogre::Vector3 resultPosition = Ogre::Math::lerp( transform->node->_getDerivedPosition(),
			                                                 desiredPostition,
			                                                 followTarget->followSpeed * delta );
			transform->node->_setDerivedPosition( resultPosition );
		}
	}
};

void InitializeScene( Gunship::Scene& scene )
{
	// add systems to scene
	scene.AddSystem< PlayerMovementSystem >();
	scene.AddSystem< CameraFollowSystem >();

	entityx::Entity camera = scene.CreateGameObject();
	Gunship::Transform::Handle cameraTransform = camera.assign<
		Gunship::Transform >( scene );
	camera.assign< Gunship::Camera >( scene, cameraTransform );
	cameraTransform->node->setPosition( 0.0f, 0.0f, 30.0f );
	cameraTransform->node->_getDerivedPositionUpdated(); // trigger ogre to recalculate derived position.
	cameraTransform->node->lookAt( Ogre::Vector3( 0.0f, 0.0f, 0.0f ),
	                               Ogre::Node::TS_WORLD );

	entityx::Entity cube = scene.CreateGameObject();
	Gunship::Transform::Handle cubeTransform =
		cube.assign< Gunship::Transform >( scene );
	cubeTransform->node->_getDerivedPositionUpdated();
	cube.assign< Gunship::Mesh >( scene, cubeTransform, "Cube.mesh" );
	cube.assign< Player >( 10.0f );

	camera.assign< FollowTarget >( cubeTransform, Ogre::Vector3( 0.0f, 0.0f, 30.0f ), 5.0f );

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
