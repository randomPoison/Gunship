#include <iostream>

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_assert.h>

#include <OgreResourceGroupManager.h>

#include "Engine.h"
#include "Scene.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Mesh.h"

Gunship::Engine::Engine() :
	_window( nullptr ),
	_root( nullptr ),
	_renderWindow( nullptr ),
	_currentScene( nullptr )
{
}

Gunship::Engine::~Engine()
{
	if ( _currentScene != nullptr )
	{
		delete _currentScene;
	}
}

bool Gunship::Engine::InitSystems()
{
	// ======================
	// INITIALIZE SDL SYSTEMS
	// ======================
	SDL_Init( SDL_INIT_EVERYTHING );

	// Create an application window with the following settings:
	_window = SDL_CreateWindow( "Gunship",                               // window title
	                            SDL_WINDOWPOS_UNDEFINED,                 // initial x position
	                            SDL_WINDOWPOS_UNDEFINED,                 // initial y position
	                            800,                                     // width, in pixels
	                            600,                                     // height, in pixels
	                            SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN ); // flags

	// Check that the window was successfully made
	if ( _window == nullptr )
	{
		// In the event that the window could not be made...
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_CreateContext( _window );

	// =======================
	// INITIALIZE OGRE SYSTEMS
	// =======================
	_root = new Ogre::Root( "", "", "" );

#if NDEBUG
	_root->loadPlugin( OGRE_PLUGIN_DIR_REL + std::string( "/RenderSystem_GL" ) );
#else
	_root->loadPlugin( OGRE_PLUGIN_DIR_DBG + std::string( "/RenderSystem_GL_d" ) );
#endif

	_root->setRenderSystem( _root->getRenderSystemByName( "OpenGL Rendering Subsystem" ) );

	_root->initialise( false );

	// get the native window manager
	struct SDL_SysWMinfo wmInfo;
	SDL_VERSION( &wmInfo.version );

	if ( SDL_GetWindowWMInfo( _window, &wmInfo ) == SDL_FALSE )
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
	params["currentGLContext"] = Ogre::String( "True" );
#endif

	_renderWindow = _root->createRenderWindow( "OGRE Window", 640, 480, false,
	                                           &params );
	_renderWindow->setVisible( true );

	// ===============================
	// INITIALIZE SCENE AND COMPONENTS
	// ===============================
	_currentScene = new Scene( this, _root, _renderWindow );

	// ================
	// INITIALIZE INPUT
	// =================
	Input::Initialize();

	// Setup Resource Groups
	Ogre::ResourceGroupManager& resourceGroupManager = Ogre::ResourceGroupManager::getSingleton();
	resourceGroupManager.createResourceGroup( "Test Resources" );
	resourceGroupManager.addResourceLocation( "Resources", "FileSystem", "Test Resources", false );
	resourceGroupManager.initialiseResourceGroup( "Test Resources" );
	resourceGroupManager.loadResourceGroup( "Test Resources" );

	return true;
}

void Gunship::Engine::ResetCurrentScene()
{
	if ( _currentScene != nullptr )
	{
		delete _currentScene;
	}

	_currentScene = new Scene( this, _root, _renderWindow );
}

void Gunship::Engine::SetupCurrentScene( SceneInitFunction initializeFunction )
{
	ResetCurrentScene();
	SDL_assert( initializeFunction != nullptr );
	initializeFunction( *_currentScene );
}

void Gunship::Engine::Start()
{
	SDL_ShowWindow( _window );

	// initialize debugging info
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastTime = startTime;
	Uint32 elapsedFrames = 0;

	// enter main loop
	bool gameRunning = true;
	while ( gameRunning )
	{
		Input::ConsumeInput();
		if ( Input::exit() )
		{
			gameRunning = false;
			continue;
		}

		// update delta time
		Uint32 currentTime = SDL_GetTicks();
		float elapsedTime = ( currentTime - lastTime ) * 0.001f;
		lastTime = currentTime;

		// debug output
		if ( Input::KeyPressed( SDL_SCANCODE_GRAVE ) )
		{
			std::cout << "Gunship Debugging Info:" << std::endl;
			std::cout << "-----------------------" << std::endl;

			// print out state of controllers
			for ( SDL_GameController* controller : Input::controllers() )
			{
				printf( "Controller:\t%s\n",
				        SDL_GameControllerName( controller ) );
				printf( "\tLeft X:\t%f\n",
				        Input::AxisValue( controller,
				                          SDL_CONTROLLER_AXIS_LEFTX ) );
				printf( "\tLeft Y:\t%f\n",
				        Input::AxisValue( controller,
				                          SDL_CONTROLLER_AXIS_LEFTY ) );
				printf( "\tRight X:\t%f\n",
				        Input::AxisValue( controller,
				                          SDL_CONTROLLER_AXIS_RIGHTX ) );
				printf( "\tRight Y:\t%f\n",
				        Input::AxisValue( controller,
				                          SDL_CONTROLLER_AXIS_RIGHTY ) );
				printf( "\tLeft Trigger:\t%f\n",
				        Input::AxisValue( controller,
				                          SDL_CONTROLLER_AXIS_TRIGGERLEFT ) );
				printf( "\tRight Trigger:\t%f\n",
				        Input::AxisValue( controller,
				                          SDL_CONTROLLER_AXIS_TRIGGERRIGHT ) );
				std::cout << std::endl;
			}

			Uint32 ticks = SDL_GetTicks();
			float fps = (float)elapsedFrames
			    / ( (float)( ticks - startTime ) / 1000.0f );
			printf( "FPS: %.2f\n", fps );
			printf( "delta: %f\n\n", elapsedTime );
			std::cout << std::endl;
			startTime = ticks;
			elapsedFrames = 0;

			printf( "Transforms:\t%lu\n", _currentScene->componentManager< Components::TransformManager >().components().count() );
			printf( "Cameras:\t%lu\n", _currentScene->componentManager< Components::CameraManager >().components().count() );
			printf( "Meshes:\t\t%lu\n", _currentScene->componentManager< Components::MeshManager >().components().count() );
			// TODO figure out how many behaviors there are.
			std::cout << std::endl;
		}

		// update behaviors
		_currentScene->Update( elapsedTime );

		// render stuffs
		_root->renderOneFrame();
		SDL_GL_SwapWindow( _window );

		// update debug info
		elapsedFrames++;
	}
}

bool Gunship::Engine::ShutDown()
{
	Input::TearDown();

	// Close and destroy the window
	SDL_DestroyWindow( _window );

	// Clean up
	SDL_Quit();

	return true;
}

Gunship::Scene* Gunship::Engine::CurrentScene()
{
	return _currentScene;
}
