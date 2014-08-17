#include "Spectacle.h"

static const float BULLET_SPEED = 20.0f;

void MakeBullet( GameObject bullet, Ogre::Vector3 start, Ogre::Vector3 dir )
{
	bullet.SetPosition( start );
	bullet.AddMesh( "BulletMesh", "ColourCube" );
	bullet.SetScale( 0.5f, 0.5f, 0.5f );
	dir.normalise();
	bullet.AddBehavior(
		[ dir ]( GameObject& bullet, Scene& scene, const Input& input, float delta )
		{
			bullet.Translate( dir * BULLET_SPEED * delta );
		} );
}
