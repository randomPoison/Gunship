#include <iostream>

#include <Gunship.h>
#include <Scene.h>
#include <GameObject.h>

#include "sillyShooter.h"

int main( int argc, char** argv )
{
	Gunship engine;

	if ( !engine.InitSystems() )
	{
		std::cout << "Could not initialize rendering systems!" << std::endl;
		return 1;
	}

	engine.ResetCurrentScene( []( Scene& scene )
	{
		GameObject* camera = scene.AddGameObject( "Camera" ).GetComponent();
		camera->AddCameraComponent();
		camera->SetPosition( 0.0f, 0.0f, 10.0f );
		camera->LookAt( 0.0f, 0.0f, 0.0f );

		GameObject* manager = scene.AddGameObject( "Manager" ).GetComponent();

		GameObject* player = scene.AddGameObject( "Player" ).GetComponent();
	} );

	engine.Start();
	engine.ShutDown();

	return 0;
}
