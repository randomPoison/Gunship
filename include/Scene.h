#pragma once

#include <vector>

#include <OgreRoot.h>
#include <OgreManualObject.h>
#include <OgreRenderWindow.h>

#include "GameObject.h"

class Scene
{
private:
	std::vector<GameObject> gameObjects;

	Ogre::Root* root;
	Ogre::SceneManager* sceneMgr;
	Ogre::RenderWindow* render;
	Ogre::Camera* camera;
	Ogre::Viewport* vp;

public:
	Scene(Ogre::Root* r, Ogre::RenderWindow* renderWindow)
	{
		root = r;
		render = renderWindow;
		sceneMgr = root->createSceneManager( Ogre::ST_GENERIC );
		camera = sceneMgr->createCamera( "cam" );

		vp = render->addViewport( camera );
		vp->setBackgroundColour( Ogre::ColourValue( 1, 0, 0, 1 ) );
	}
};
