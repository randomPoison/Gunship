#include <iostream>

#include <Gunship.h>

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
		GameObject camera = scene.AddGameObject( "Camera" );
		camera.AddCamera();
		camera.SetPosition( 0.0f, 0.0f, 10.0f );
		camera.LookAt( 0.0f, 0.0f, 0.0f );

		GameObject manager = scene.AddGameObject( "Manager" );

		GameObject player = scene.AddGameObject( "Player" );
		player.SetPosition( -3.5f, 0.0f, 0.0f );
		player.AddBehavior( []( GameObject& gameObject )
		{
			gameObject.Translate( 0.001f, 0.0f, 0.0f );
		} );
		player.AddMesh( "playerMesh", "ColourCube");
	} );

	engine.Start();
	engine.ShutDown();

	return 0;
}
