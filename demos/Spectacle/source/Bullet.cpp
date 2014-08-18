#include "Spectacle.h"

static const float BULLET_SPEED = 0.5f;
static const float BULLET_LIFE = 1000.0f;

void MakeBullet( GameObject& bullet, Ogre::Vector3 start, Ogre::Vector3 dir )
{
	bullet.SetPosition( start );
	bullet.AddMesh( "BulletMesh", "ColourCube" );
	bullet.SetScale( 0.5f, 0.5f, 0.5f );
	float life = 0.0f;
	bullet.AddBehavior(
		[ dir, life ]( GameObject& bullet, Scene& scene, const Input& input ) mutable
		{
			bullet.Translate( dir * BULLET_SPEED );

			life += 1.0f;
			if ( life > BULLET_LIFE )
			{
				bullet.Destroy();
			}
		} );
}
