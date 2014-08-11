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

	Scene* scene = engine.CurrentScene();

	float playerSpeed = 0.05f;
	GameObject player = scene->AddGameObject( "Player" );
	player.AddMesh( "playerMesh", "ColourCube");
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

	GameObject target = scene->AddGameObject( "Target" );
	target.AddMesh( "targetMesh", "ColourCube" );
	player.AddChild( target );
	target.SetPosition( 0.0f, 2.0f, 0.0f );
	target.SetScale( 0.25f, 0.25f, 0.25f );

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
