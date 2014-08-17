#include "Spectacle.h"

static const float BULLET_DELAY = 0.1f;
static const float PLAYER_BASE_SPEED = 10.0f;

void MakePlayer( GameObject& player, GameObject& target )
{
	player.AddMesh( "playerMesh", "ColourCube" );
	player.SetPosition( 0.0f, 0.0f, 0.0f );
	player.AddBehavior(
		[ &target ]( GameObject& gameObject, Scene& scene, const Input& input, float delta )
		{
			static float cooldown = 0.0f;
			static float playerSpeed = PLAYER_BASE_SPEED * delta;

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

			float xTrans = input.AxisValue( 0, SDL_CONTROLLER_AXIS_LEFTX );
			float yTrans = input.AxisValue( 0, SDL_CONTROLLER_AXIS_LEFTY );

			gameObject.Translate( xTrans * playerSpeed, yTrans * -playerSpeed, 0.0f );

			gameObject.LookAt( target );

			xTrans = input.AxisValue( 0, SDL_CONTROLLER_AXIS_RIGHTX );
			yTrans = input.AxisValue( 0, SDL_CONTROLLER_AXIS_RIGHTY );
			Ogre::Vector2 bulletDir( xTrans, yTrans );

			cooldown -= delta;
			if ( cooldown < 0.0f && bulletDir.length() > 0.9f )
			{
				MakeBullet( scene.AddGameObject( "Bullet" ), gameObject.Position(), Ogre::Vector3( xTrans, -yTrans, 0.0f ) );
				cooldown = BULLET_DELAY;
			}
		} );

	target.AddMesh( "targetMesh", "ColourCube" );
	target.SetPosition( 0.0f, 2.0f, 0.0f );
	target.SetScale( 0.25f, 0.25f, 0.25f );

	target.AddBehavior(
		[ &player ]( GameObject& gameObject, Scene& scene, const Input& input, float delta )
		{
			static float offset = 2.0f;

			Ogre::Vector3 pos = player.Position();
			float xTrans = input.AxisValue( 0, SDL_CONTROLLER_AXIS_RIGHTX );
			float yTrans = input.AxisValue( 0, SDL_CONTROLLER_AXIS_RIGHTY );
			gameObject.SetPosition( pos.x + xTrans * offset, pos.y + -yTrans * offset, pos.z + 0.0f );
		} );
}
