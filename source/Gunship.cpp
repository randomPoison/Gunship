#include <SDL.h>
#include <SDL_syswm.h>
#include <iostream>

#include <OgreRoot.h>
#include <OgreManualObject.h>
#include <OgreRenderWindow.h>

#include "Gunship.h"
#include "Scene.h"

Gunship::Gunship() : currentScene( nullptr ) { }

Gunship::~Gunship()
{
	if ( currentScene != nullptr )
	{
		delete currentScene;
	}
}

bool Gunship::InitSystems()
{
	SDL_Init( SDL_INIT_VIDEO );

	// Create an application window with the following settings:
	window = SDL_CreateWindow( 
		"Gunship",								// window title
		SDL_WINDOWPOS_UNDEFINED,				// initial x position
		SDL_WINDOWPOS_UNDEFINED,				// initial y position
		640,									// width, in pixels
		480,									// height, in pixels
		SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN	// flags
	);

	// Check that the window was successfully made
	if( window == NULL )
	{
		// In the event that the window could not be made...
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext( window );

	root = new Ogre::Root( "", "", "" );

	// TODO: Unfuck this bit of fragmentation here.
	// This is only happening because I can't find the debug plugins for Ogre on my system.
	// Either they don't come with default universe install, or I'm too unfamiliar
	// with linux development to find them (and cmake isn't doing it for me).
#ifdef WIN32
	root->loadPlugin ( OGRE_PLUGIN_DIR_DBG + std::string( "/RenderSystem_GL_d" ) );
#else
	root->loadPlugin ( OGRE_PLUGIN_DIR_REL + std::string( "/RenderSystem_GL" ) );
#endif
	root->setRenderSystem( root->getRenderSystemByName( "OpenGL Rendering Subsystem" ) );

	root->initialise( false );

	// get the native window manager
	struct SDL_SysWMinfo wmInfo;
	SDL_VERSION( &wmInfo.version );

	if ( SDL_GetWindowWMInfo( window, &wmInfo ) == SDL_FALSE )
	{
		std::cout << "Couldn't get WM Info!" << std::endl;
		return false;
	}

	Ogre::NameValuePairList params;
	params.insert( std::make_pair( "FSAA", "0" ) );
	params.insert( std::make_pair( "vsync", "false" ) );

#ifdef WIN32
	params["externalWindowHandle"] = Ogre::StringConverter::toString( reinterpret_cast<size_t>( wmInfo.info.win.window ) );
	params["externalGLContext"] = "True";
	params["externalGLControl"] = "True";
#else
	params["parentWindowHandle"] = Ogre::StringConverter::toString( reinterpret_cast<unsigned long>( wmInfo.info.x11.window ) );
#endif

	renderWindow = Ogre::Root::getSingleton().createRenderWindow( "OGRE Window", 640, 480, false, &params );

	// initialize the current scene
	currentScene = new Scene( root, renderWindow );
	GameObject* obj = currentScene->AddGameObject( "Camera" ).GetComponent();
	obj->AddCameraComponent();

	return true;
}

void Gunship::Start()
{
	SDL_ShowWindow( window );

	// enter main loop
	while( true )
	{
		UpdateComponents();

		root->renderOneFrame();
		SDL_GL_SwapWindow( window );

		SDL_Event event;
		if( SDL_PollEvent( &event ) )
		{
			if ( event.type == SDL_QUIT )
			{
				break;
			}
		}
	}
}

bool Gunship::ShutDown()
{
	delete root;

	// Close and destroy the window
	SDL_DestroyWindow( window ); 

	// Clean up
	SDL_Quit();

	return true;
}

void Gunship::UpdateComponents()
{
	// TODO someday there will be something here
}

Scene* Gunship::CurrentScene()
{
	return currentScene;
}

Scene* Gunship::ResetCurrentScene()
{
	delete currentScene;
	currentScene = new Scene( root, renderWindow );
	return currentScene;
}
