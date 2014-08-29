#include "Spectacle.h"

static const float BULLET_SPEED = 50.0f;
static const float BULLET_LIFE = 5.0f;

void MakeBullet( GameObject bullet, Ogre::Vector3 start, Ogre::Vector3 dir )
{
	bullet.SetPosition( start );
	bullet.AddMesh( "BulletMesh", "ColourCube" );
	bullet.SetScale( 0.5f, 0.5f, 0.5f );
	bullet.AddCollider( 0.5f );
	float life = 0.0f;
	dir.normalise();
	bullet.AddBehavior(
		[ dir, life ]( GameObject& bullet, Scene& scene, const Input& input, float delta ) mutable
		{
			bullet.Translate( dir * BULLET_SPEED * delta );

			life += delta;
			if ( life > BULLET_LIFE )
			{
				bullet.Destroy();
			}
		} );
}
