#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <Compositor/OgreCompositorManager2.h>

#include "Components/Camera.h"
#include "Scene.h"

Gunship::Camera::Camera( const Scene& scene, const Transform::Handle& transform, const char* cameraName )
{
	// create camera and add it to scene heirarchy
	camera = scene.sceneManager().createCamera( cameraName );
	camera->detachFromParent();
	transform->node->attachObject( camera );

	// setup the camera's compositor
	// each camera get's a workspace.
	// This probably isn't a good idea.
	Ogre::CompositorManager2* pCompositorManager =
		scene.ogreRoot().getCompositorManager2();
	const Ogre::String workspaceName = "scene workspace";
	const Ogre::IdString workspaceNameHash = workspaceName;
	pCompositorManager->createBasicWorkspaceDef( workspaceName,
	                                             Ogre::ColourValue::Red );
	pCompositorManager->addWorkspace( &scene.sceneManager(),
	                                  &scene.renderWindow(),
	                                  camera,
	                                  workspaceNameHash,
	                                  true );
}
