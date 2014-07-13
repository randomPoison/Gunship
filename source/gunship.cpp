#include <SDL.h>
#include <SDL_syswm.h>
#include <iostream>

#include <OgreRoot.h>
#include <OgreManualObject.h>
#include <OgreRenderWindow.h>

// NOTE THIS IS A SUPER HACKY TEMPORARY VALUE
// UNTIL I CAN BE BOTHERED TO GET CMAKE SETUP CORRECTLY
#define WINDOWS

bool InitRenderingSystems( SDL_Window* window, Ogre::Root* root, Ogre::RenderWindow* render )
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
	root->loadPlugin ( OGRE_PLUGIN_DIR_DBG + std::string( "/RenderSystem_GL_d" ) );
	root->setRenderSystem( root->getRenderSystemByName( "OpenGL Rendering Subsystem" ) );

	root->initialise( false );

	//get the native whnd
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

#ifdef WINDOWS
	params["externalWindowHandle"] = Ogre::StringConverter::toString( reinterpret_cast<size_t>( wmInfo.info.win.window ) );
	params["externalGLContext"] = "True";
	params["externalGLControl"] = "True";
#else
	switch ( wmInfo.subsystem )
	{
	case SDL_SYSWM_X11:
		winHandle = Ogre::StringConverter::toString( (unsigned long)wmInfo.info.x11.window );
		params["currentGLContext"] = "True";
		break;
	default:
		throw std::runtime_error( "Unexpected WM!" );
		break;
	}
#endif

	render = Ogre::Root::getSingleton().createRenderWindow( "OGRE Window", 640, 480, false, &params );

	return true;
}

int main( int argc, char** argv )
{
	SDL_Window* window;
	Ogre::Root* root;
	Ogre::RenderWindow* render;

	if ( !InitRenderingSystems( window, root, render ) )
	{
		std::cout << "Could not initialize rendering systems!" << std::endl;
	}

	Ogre::SceneManager* sceneMgr = root->createSceneManager( Ogre::ST_GENERIC );
	Ogre::Camera* camera = sceneMgr->createCamera( "cam" );
	Ogre::Viewport* vp = render->addViewport( camera );
	vp->setBackgroundColour( Ogre::ColourValue( 1, 0, 0, 1 ) );

	SDL_ShowWindow( window );

	while( true )
	{
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

	delete root;

	// Close and destroy the window
	SDL_DestroyWindow( window ); 

	// Clean up
	SDL_Quit();

	return 0;
}
