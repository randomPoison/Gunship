#include "Spectacle.h"

void MakeCamera( GameObject& camera, GameObject& cameraAnchor, GameObject& player )
{
	player.AddChild( cameraAnchor );
	cameraAnchor.SetPosition( 0.0f, 40.0f, 0.0f );

	camera.AddCamera();
	camera.LookAt( player );
	camera.AddBehavior(
			[ &cameraAnchor, &player ]( GameObject& gameObject, Scene& scene, const Input& input )
			{
				Ogre::Vector3 offset = cameraAnchor.Position() - gameObject.Position();
				Ogre::Vector3 pos = gameObject.Position() + ( offset * 0.01f );
				gameObject.SetPosition( pos.x, pos.y, pos.z );
			} );
}
