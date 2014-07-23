#include <OgreRoot.h>
#include <OgreManualObject.h>
#include <OgreRenderWindow.h>

#include "Scene.h"

Scene::Scene( Ogre::Root* root, Ogre::RenderWindow* render ) : root( root ), renderWindow( render )
{
	sceneManager = root->createSceneManager( Ogre::ST_GENERIC );
	camera = sceneManager->createCamera( "cam" );

	viewport = renderWindow->addViewport( camera );
	viewport->setBackgroundColour( Ogre::ColourValue( 1, 0, 0, 1 ) );
}