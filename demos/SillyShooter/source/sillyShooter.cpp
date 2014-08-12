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

	GameObject player = scene->AddGameObject( "Player" );
	GameObject target = scene->AddGameObject( "Target" );
	GameObject camera = scene->AddGameObject( "Camera" );
	GameObject cameraAnchor = scene->AddGameObject( "CameraAnchor" );

	player.AddMesh( "playerMesh", "ColourCube");
	player.SetPosition( 0.0f, 0.0f, 0.0f );
	float playerSpeed = 0.05f;
	player.AddBehavior( [ &playerSpeed, &target ]( GameObject& gameObject, const Input& input )
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

		gameObject.LookAt( target );
	} );

	target.AddMesh( "targetMesh", "ColourCube" );
	target.SetPosition( 0.0f, 2.0f, 0.0f );
	target.SetScale( 0.25f, 0.25f, 0.25f );
	float offset = 2.0f;
	target.AddBehavior( [ &player, &offset ]( GameObject& gameObject, const Input& input )
	{
		Ogre::Vector3 pos = player.Position();
		gameObject.SetPosition( pos.x + input.AxisValue( 0, 2 ) * offset, pos.y + -input.AxisValue( 0, 3 ) * offset, pos.z + 0.0f );
	} );

	player.AddChild( cameraAnchor );
	cameraAnchor.SetPosition( 0.0f, 40.0f, 0.0f );

	camera.AddCamera();
	camera.LookAt( player );
	camera.AddBehavior( [ &cameraAnchor, &player ]( GameObject& gameObject, const Input& input )
	{
		Ogre::Vector3 offset = cameraAnchor.Position() - gameObject.Position();
		Ogre::Vector3 pos = gameObject.Position() + ( offset * 0.01f );
		gameObject.SetPosition( pos.x, pos.y, pos.z );
	} );

	GameObject manager = scene->AddGameObject( "Manager" );

	engine.Start();
	engine.ShutDown();

	return 0;
}
