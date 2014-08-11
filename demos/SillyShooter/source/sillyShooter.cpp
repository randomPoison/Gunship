#include <iostream>

#include <Gunship.h>

#include "sillyShooter.h"

int main( int argc, char* argv[] )
{
	Gunship engine;
	if ( !engine.InitSystems() )
	{
		std::cout << "Could not initialize rendering systems!" << std::endl;
		return 1;
	}

	float playerSpeed = 0.05f;
	Scene* scene = engine.CurrentScene();
	GameObject player = scene->AddGameObject( "Player" );
	player.SetPosition( 0.0f, 0.0f, 0.0f );
	player.AddBehavior( [ playerSpeed ]( GameObject& gameObject, const Input& input )
	{
		if ( input.KeyPressed( SDLK_w ) )
		{
			gameObject.Translate( 0.0f, playerSpeed, 0.0f );
		}
		if ( input.KeyPressed( SDLK_a ) )
		{
			gameObject.Translate( -playerSpeed, 0.0f, 0.0f );
		}
		if ( input.KeyPressed( SDLK_s ) )
		{
			gameObject.Translate( 0.0f, -playerSpeed, 0.0f );
		}
		if ( input.KeyPressed( SDLK_d ) )
		{
			gameObject.Translate( playerSpeed, 0.0f, 0.0f );
		}

		gameObject.Translate( input.AxisValue( 0, 0 ) * playerSpeed, input.AxisValue( 0, 1 ) * -playerSpeed, 0.0f );
	} );
	player.AddMesh( "playerMesh", "ColourCube");

	GameObject camera = scene->AddGameObject( "Camera" );
	camera.AddCamera();
	camera.SetPosition( 0.0f, 0.0f, 10.0f );
	camera.LookAt( 0.0f, 0.0f, 0.0f );
	camera.AddBehavior( [ &player ]( GameObject& gameObject, const Input& input )
	{
		gameObject.LookAt( player );
	} );

	GameObject manager = scene->AddGameObject( "Manager" );

	engine.Start();
	engine.ShutDown();

	return 0;
}
