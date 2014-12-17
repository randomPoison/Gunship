#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "Engine.h"
#include "Scene.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Mesh.h"

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
