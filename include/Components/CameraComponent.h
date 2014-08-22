#pragma once

class GameObject;

struct CameraComponent : public Component
{
	CameraComponent( GameObject& owner, Ogre::Camera* cam, Ogre::Viewport* view );

	Ogre::Camera* camera;
	Ogre::Viewport* viewport;
};
