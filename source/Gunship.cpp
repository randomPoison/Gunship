#include "Engine.h"
#include "Scene.h"
#include "Components/Transform.h"
#include "Components/Camera.h"

void InitializeScene( Gunship::Scene& scene )
{
	entityx::Entity gameObject = scene.entities.create();
	Gunship::Transform::Handle transform = gameObject.assign< Gunship::Transform >( scene );
	Gunship::Camera::Handle camera = gameObject.assign< Gunship::Camera >( scene, transform );
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
