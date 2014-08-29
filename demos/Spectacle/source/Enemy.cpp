#include "Spectacle.h"

static const float BULLET_DELAY = 0.3f;

void MakeEnemy( GameObject enemy, GameObject& player, Ogre::Vector3 start )
{
	enemy.AddMesh( "EnemyMesh", "ColourCube" );
	enemy.SetPosition( start );
	enemy.AddCollider( 1.0f );
	float cooldown = 0.0f;
	enemy.AddBehavior( [ &player, cooldown ]( GameObject& enemy, Scene& scene, const Input& input, float delta ) mutable
		{
			//enemy.LookAt( player );
			cooldown += delta;
			if ( cooldown > BULLET_DELAY )
			{
				Ogre::Vector3 bulletDir = player.Position() - enemy.Position();
				MakeBullet( scene.AddGameObject( "Bullet" ), enemy.Position(), bulletDir );
				cooldown -= BULLET_DELAY;
			}
		} );
}
