#include "Engine.h"
#include "Scene.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Mesh.h"
#include "Components/Light.h"

void InitializeScene( Gunship::Scene& scene )
{
	entityx::Entity camera = scene.entities.create();
	Gunship::Transform::Handle cameraTransform = camera.assign< Gunship::Transform >( scene );
	camera.assign< Gunship::Camera >( scene, cameraTransform );
	cameraTransform->node->setPosition( 20.0f, 15.0f, 30.0f );
	cameraTransform->node->_getDerivedPositionUpdated(); // trigger ogre to recalculate derived position.
	cameraTransform->node->lookAt( Ogre::Vector3( 0.0f, 0.0f, 0.0f ), Ogre::Node::TS_WORLD );

	entityx::Entity cube = scene.entities.create();
	Gunship::Transform::Handle cubeTransform = cube.assign< Gunship::Transform >( scene );
	cube.assign< Gunship::Mesh >( scene, cubeTransform, "Cube.mesh" );

	entityx::Entity light = scene.entities.create();
	Gunship::Transform::Handle lightTransform = light.assign< Gunship::Transform >( scene );
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
