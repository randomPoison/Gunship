#include "Spectacle.h"

static const float BULLET_SPEED = 0.5f;

void MakeBullet( GameObject& bullet, Ogre::Vector3 start, Ogre::Vector3 dir )
{
	bullet.SetPosition( start );
	bullet.AddMesh( "BulletMesh", "ColourCube" );
	bullet.SetScale( 0.5f, 0.5f, 0.5f );
	bullet.AddBehavior( [ dir ]( GameObject& bullet, Scene& scene, const Input& input )
	{
		bullet.Translate( dir * BULLET_SPEED );
	} );
}
