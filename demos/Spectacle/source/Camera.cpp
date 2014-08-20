#include "Spectacle.h"

void MakeCamera(
	GameObject& camera,
	GameObject& cameraAnchor,
	GameObject& player )
{
	player.AddChild( cameraAnchor );
	cameraAnchor.SetPosition( 0.0f, 80.0f, 0.0f );

	camera.AddCamera();
	camera.LookAt( player );
	camera.AddBehavior(
		[ &cameraAnchor, &player ]( GameObject& gameObject, Scene& scene, const Input& input, float delta )
		{
			// TODO make the lag effect be a function of time so that its not so effected by framerate.
			Ogre::Vector3 offset = cameraAnchor.Position() - gameObject.Position();
			Ogre::Vector3 pos = gameObject.Position() + ( offset * 1.0f * delta );
			gameObject.SetPosition( pos.x, pos.y, pos.z );
		} );
}
