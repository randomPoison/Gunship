#include <iostream>

#include "Spectacle.h"

int main( int argc, char* argv[] )
{
	Gunship engine;
	if ( !engine.InitSystems() )
	{
		std::cout << "Could not initialize rendering systems!" << std::endl;
		return 1;
	}

	Scene* scene = engine.CurrentScene();

	GameObject player = scene->AddGameObject( "Player" );
	GameObject target = scene->AddGameObject( "Target" );
	GameObject camera = scene->AddGameObject( "Camera" );
	GameObject cameraAnchor = scene->AddGameObject( "CameraAnchor" );

	MakePlayer( player, target );
	MakeCamera( camera, cameraAnchor, player );

	//GameObject manager = scene->AddGameObject( "Manager" );

	engine.Start();
	engine.ShutDown();

	return 0;
}
