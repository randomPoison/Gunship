#include <iostream>

#include <SDL.h>

#include "Gunship.h"

// temporary includes for createColourCube()
#include <OgreMeshManager.h>
#include <OgreHardwareBufferManager.h>
#include <OgreSubMesh.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

void createColourCube()
{
	using namespace Ogre;

	/// Create the mesh via the MeshManager
	MeshPtr msh = MeshManager::getSingleton().createManual( "ColourCube", "General" );

	/// Create one submesh
	SubMesh* sub = msh->createSubMesh();

	const float sqrt13 = 0.577350269f; /* sqrt(1/3) */

	/// Define the vertices (8 vertices, each consisting of 2 groups of 3 floats
	const size_t nVertices = 8;
	const size_t vbufCount = 3 * 2 * nVertices;
	float vertices[vbufCount] =
		{
			-1.0, 1.0, -1.0,				//0 position
			-sqrt13, sqrt13, -sqrt13,		//0 normal
			1.0, 1.0, -1.0,				//1 position
			sqrt13, sqrt13, -sqrt13,		//1 normal
			1.0, -1.0, -1.0,				//2 position
			sqrt13, -sqrt13, -sqrt13,		//2 normal
			-1.0, -1.0, -1.0,				//3 position
			-sqrt13, -sqrt13, -sqrt13,	//3 normal
			-1.0, 1.0, 1.0,				//4 position
			-sqrt13, sqrt13, sqrt13,		//4 normal
			1.0, 1.0, 1.0,				//5 position
			sqrt13, sqrt13, sqrt13,		//5 normal
			1.0, -1.0, 1.0,				//6 position
			sqrt13, -sqrt13, sqrt13,		//6 normal
			-1.0, -1.0, 1.0,				//7 position
			-sqrt13, -sqrt13, sqrt13,		//7 normal
		};

	RenderSystem* rs = Root::getSingleton().getRenderSystem();
	RGBA colours[nVertices];
	RGBA *pColour = colours;
	// Use render system to convert colour value since colour packing varies
	rs->convertColourValue( ColourValue( 1.0, 0.0, 0.0 ), pColour++ ); //0 colour
	rs->convertColourValue( ColourValue( 1.0, 1.0, 0.0 ), pColour++ ); //1 colour
	rs->convertColourValue( ColourValue( 0.0, 1.0, 0.0 ), pColour++ ); //2 colour
	rs->convertColourValue( ColourValue( 0.0, 0.0, 0.0 ), pColour++ ); //3 colour
	rs->convertColourValue( ColourValue( 1.0, 0.0, 1.0 ), pColour++ ); //4 colour
	rs->convertColourValue( ColourValue( 1.0, 1.0, 1.0 ), pColour++ ); //5 colour
	rs->convertColourValue( ColourValue( 0.0, 1.0, 1.0 ), pColour++ ); //6 colour
	rs->convertColourValue( ColourValue( 0.0, 0.0, 1.0 ), pColour++ ); //7 colour

	/// Define 12 triangles (two triangles per cube face)
	/// The values in this table refer to vertices in the above table
	const size_t ibufCount = 36;
	unsigned short faces[ibufCount] =
		{
			0, 2, 3,
			0, 1, 2,
			1, 6, 2,
			1, 5, 6,
			4, 6, 5,
			4, 7, 6,
			0, 7, 4,
			0, 3, 7,
			0, 5, 1,
			0, 4, 5,
			2, 7, 3,
			2, 6, 7
		};

	/// Create vertex data structure for 8 vertices shared between submeshes
	msh->sharedVertexData = new VertexData();
	msh->sharedVertexData->vertexCount = nVertices;

	/// Create declaration (memory format) of vertex data
	VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
	size_t offset = 0;
	// 1st buffer
	decl->addElement( 0, offset, VET_FLOAT3, VES_POSITION );
	offset += VertexElement::getTypeSize( VET_FLOAT3 );
	decl->addElement( 0, offset, VET_FLOAT3, VES_NORMAL );
	offset += VertexElement::getTypeSize( VET_FLOAT3 );
	/// Allocate vertex buffer of the requested number of vertices (vertexCount) 
	/// and bytes per vertex (offset)
	HardwareVertexBufferSharedPtr vbuf =
		HardwareBufferManager::getSingleton().createVertexBuffer(
			offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY );
	/// Upload the vertex data to the card
	vbuf->writeData( 0, vbuf->getSizeInBytes(), vertices, true );

	/// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
	VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding;
	bind->setBinding( 0, vbuf );

	// 2nd buffer
	offset = 0;
	decl->addElement( 1, offset, VET_COLOUR, VES_DIFFUSE );
	offset += VertexElement::getTypeSize( VET_COLOUR );
	/// Allocate vertex buffer of the requested number of vertices (vertexCount) 
	/// and bytes per vertex (offset)
	vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(
		offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY );
	/// Upload the vertex data to the card
	vbuf->writeData( 0, vbuf->getSizeInBytes(), colours, true );

	/// Set vertex buffer binding so buffer 1 is bound to our colour buffer
	bind->setBinding( 1, vbuf );

	/// Allocate index buffer of the requested number of vertices (ibufCount) 
	HardwareIndexBufferSharedPtr ibuf = HardwareBufferManager::getSingleton().
		createIndexBuffer(
		HardwareIndexBuffer::IT_16BIT,
		ibufCount,
		HardwareBuffer::HBU_STATIC_WRITE_ONLY );

	/// Upload the index data to the card
	ibuf->writeData( 0, ibuf->getSizeInBytes(), faces, true );

	/// Set parameters of the submesh
	sub->useSharedVertices = true;
	sub->indexData->indexBuffer = ibuf;
	sub->indexData->indexCount = ibufCount;
	sub->indexData->indexStart = 0;

	/// Set bounding information (for culling)
	msh->_setBounds( AxisAlignedBox( -100, -100, -100, 100, 100, 100 ) );
	msh->_setBoundingSphereRadius( Math::Sqrt( 3 * 100 * 100 ) );

	/// Notify -Mesh object that it has been loaded
	msh->load();

	MaterialPtr material = MaterialManager::getSingleton().create(
		"Test/ColourTest", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
	material->getTechnique( 0 )->getPass( 0 )->setVertexColourTracking( TVC_AMBIENT );
}

// Blatantly stolen from the shell.cc example that comes with v8.
// currently being used as a placeholder until I can be bothered to
// add some better logging functionality.
void Print( const v8::FunctionCallbackInfo< v8::Value >& args )
{
	bool first = true;
	for ( int i = 0; i < args.Length(); i++ )
	{
		v8::HandleScope handle_scope( args.GetIsolate() );
		if ( first )
		{
			first = false;
		}
		else
		{
			printf( " " );
		}
		v8::String::Utf8Value str( args[i] );
		const char* cstr = *str;
		printf( "%s", cstr );
	}
	printf( "\n" );
	fflush( stdout );
}

Gunship::Gunship() :
	currentScene( nullptr )
{
}

Gunship::~Gunship()
{
	if ( currentScene != nullptr )
	{
		delete currentScene;
	}
}

bool Gunship::InitSystems()
{
	// ======================
	// INITIALIZE SDL SYSTEMS
	// ======================
	SDL_Init( SDL_INIT_EVERYTHING );

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"Gunship",								// window title
		SDL_WINDOWPOS_UNDEFINED,				// initial x position
		SDL_WINDOWPOS_UNDEFINED,				// initial y position
		800,									// width, in pixels
		600,									// height, in pixels
		SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN	// flags
			);

	// Check that the window was successfully made
	if ( window == nullptr )
	{
		// In the event that the window could not be made...
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_CreateContext( window );

	// =======================
	// INITIALIZE OGRE SYSTEMS
	// =======================
	root = new Ogre::Root( "", "", "" );

	// TODO: Unfuck this bit of fragmentation here.
	// This is only happening because I can't find the debug plugins for Ogre on my system.
	// Either they don't come with default universe install, or I'm too unfamiliar
	// with linux development to find them (and cmake isn't doing it for me).
#if defined(_DEBUG) && defined(WIN32)
	root->loadPlugin( OGRE_PLUGIN_DIR_DBG + std::string( "/RenderSystem_GL_d" ) );
#else
	root->loadPlugin( OGRE_PLUGIN_DIR_REL + std::string( "/RenderSystem_GL" ) );
#endif

	root->setRenderSystem(
		root->getRenderSystemByName( "OpenGL Rendering Subsystem" ) );

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
	params["currentGLContext"] = Ogre::String( "True" );
#endif

	renderWindow = root->createRenderWindow( "OGRE Window", 640, 480, false,
		&params );
	renderWindow->setVisible( true );

	// ===============================
	// INITIALIZE SCENE AND COMPONENTS
	// ===============================
	currentScene = new Scene( this, root, renderWindow );

	// initialize primitive meshes
	createColourCube();

	// initialize joysticks and whatnot
	if ( SDL_NumJoysticks() > 0 )
	{
		printf( "num joysticks: %d\n", SDL_NumJoysticks() );
		SDL_GameController* controller = SDL_GameControllerOpen( 0 );

		std::cout << "joystick is controller: "
			<< ( SDL_IsGameController( 0 ) ? "true" : "false" ) << std::endl;

		if ( controller == nullptr )
		{
			printf( "Warning: Unable to open game controller! SDL Error: %s\n",
				SDL_GetError() );
			return false;
		}
		input.controllers.push_back( controller );
	}

	InitializeV8();

	return true;
}

bool Gunship::InitializeV8()
{
	// create v8 Isolate
	isolate = v8::Isolate::New();

	// create local scope
	v8::Isolate::Scope isolateScope( isolate );
	v8::HandleScope handleScope( isolate );

	v8::Local< v8::ObjectTemplate > _global = v8::ObjectTemplate::New();

	// GLOBAL GUNSHIP OBJECT
	v8::Local< v8::ObjectTemplate > _gunship = v8::ObjectTemplate::New();
	_gunship->SetInternalFieldCount( 1 );

	// make game object template
	v8::Local< v8::FunctionTemplate > _gameObject = V8_FUNCTION_TEMPLATE( isolate, GameObjectComponent::CreateGameObjectComponent );
	_gameObject->SetClassName( v8::String::NewFromUtf8( isolate, "GameObject" ) );
	v8::Local< v8::ObjectTemplate > _gameObjectInstance = _gameObject->InstanceTemplate();
	v8::Local< v8::ObjectTemplate > _gameObjectPrototype = _gameObject->PrototypeTemplate();

	// GAMEOBJECT PROTOTYPE
	_gameObjectPrototype->Set( isolate, "AddCamera", V8_FUNCTION_TEMPLATE( isolate, GameObjectComponent::AddCameraComponent ) );
	_gameObjectPrototype->Set( isolate, "AddMesh", V8_FUNCTION_TEMPLATE( isolate, GameObjectComponent::AddMesh ) );
	_gameObjectPrototype->Set( isolate, "SetPosition", V8_FUNCTION_TEMPLATE( isolate, GameObjectComponent::SetPosition ) );
	_gameObjectPrototype->Set( isolate, "SetPositionByValue", V8_FUNCTION_TEMPLATE( isolate, GameObjectComponent::SetPositionByValue ) );
	_gameObjectPrototype->Set( isolate, "Translate", V8_FUNCTION_TEMPLATE( isolate, GameObjectComponent::Translate ) );
	_gameObjectPrototype->Set( isolate, "TranslateByValue", V8_FUNCTION_TEMPLATE( isolate, GameObjectComponent::TranslateByValue ) );
	_gameObjectPrototype->Set( isolate, "SetScale", V8_FUNCTION_TEMPLATE( isolate, GameObjectComponent::SetScale ) );
	_gameObjectPrototype->Set( isolate, "SetScaleByValue", V8_FUNCTION_TEMPLATE( isolate, GameObjectComponent::SetScaleByValue ) );
	_gameObjectPrototype->Set( isolate, "GetPosition", V8_FUNCTION_TEMPLATE( isolate, GameObjectComponent::GetPosition ) );

	// GAMEOBJECT INSTANCES
	_gameObjectInstance->Set( isolate, "id", V8_UNSIGNED( isolate, -1 ) );
	_gameObjectInstance->Set( isolate, "index", V8_UNSIGNED( isolate, -1 ) );
	_gameObjectInstance->Set( isolate, "hasCamera", V8_BOOL( isolate, false ) );
	_gameObjectInstance->Set( isolate, "name", V8_STRING( isolate, "__BAD_GAMEOBJECT_NAME__" ) );

	_gunship->Set( isolate, "GameObject", _gameObject );
	_global->Set( isolate, "Gunship", _gunship );
	_global->Set( isolate, "print", V8_FUNCTION_TEMPLATE( isolate, Print ) );

	// CREATE CONTEXT
	v8::Local< v8::Context > context = v8::Context::New( isolate, nullptr, _global );
	_context.Reset( isolate, context );
	v8::Context::Scope contextScope( context );

	// give global instance pointers to gunship objects and whatnot
	v8::Local< v8::Object > global = context->Global();
	v8::Local< v8::Object > gunship = global->Get( V8_STRING( isolate, "Gunship" ) )->ToObject();
	gunship->SetInternalField( 0, v8::External::New( isolate, this ) );

	// RUN STARTUP SCRIPTS
	// gunship startup
	RunStartupScript( "startup.js" );

	// gl-matrix startup
#ifdef _DEBUG
	RunStartupScript( "gl-matrix/gl-matrix.js" );
#else
	RunStartupScript( "gl-matrix/gl-matrix-min.js" );
#endif

	RunStartupScript( "SDL_scancode.js" );

	return true;
}

void Gunship::Start()
{
	SDL_ShowWindow( window );

	// create scope for v8
	v8::Isolate::Scope isolateScope( isolate );
	v8::HandleScope handleScope( isolate );
	v8::Local< v8::Context > context = v8::Local< v8::Context >::New( isolate, _context );
	v8::Context::Scope contextScope( context );

	// run game script
	std::string gameScript = LoadScript( "game.js" );
	{
		v8::TryCatch tryCatch;

		v8::Local< v8::Script > script = v8::Script::Compile(
			V8_STRING( isolate, gameScript.c_str() ) );
		v8::Local< v8::Value > result = script->Run();
		v8::String::Utf8Value utf8( result );

		if ( tryCatch.HasCaught() )
		{
			printf( "game script has failed:\n" );
			ReportException( isolate, tryCatch );
		}
	}

	// initialize debugging info
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastTime = startTime;
	Uint32 elapsedFrames = 0;

	// enter main loop
	bool gameRunning = true;
	while ( gameRunning )
	{
		input.ConsumeInput();
		if ( input.exit )
		{
			gameRunning = false;
			continue;
		}

		// update delta time
		Uint32 currentTime = SDL_GetTicks();
		float elapsedTime = ( currentTime - lastTime ) * 0.001f;
		lastTime = currentTime;

		// debug output
		if ( input.KeyPressed( SDLK_BACKQUOTE ) )
		{
			std::cout << "Gunship Debugging Info:" << std::endl;
			std::cout << "-----------------------" << std::endl;

			// print out state of controllers
			for ( SDL_GameController* controller : input.controllers )
			{
				printf( "Controller:\t%s\n", SDL_GameControllerName( controller ) );
				printf( "\tLeft X:\t%f\n", input.AxisValue( controller, SDL_CONTROLLER_AXIS_LEFTX ) );
				printf( "\tLeft Y:\t%f\n", input.AxisValue( controller, SDL_CONTROLLER_AXIS_LEFTY ) );
				printf( "\tRight X:\t%f\n", input.AxisValue( controller, SDL_CONTROLLER_AXIS_RIGHTX ) );
				printf( "\tRight Y:\t%f\n", input.AxisValue( controller, SDL_CONTROLLER_AXIS_RIGHTY ) );
				printf( "\tLeft Trigger:\t%f\n", input.AxisValue( controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT ) );
				printf( "\tRight Trigger:\t%f\n", input.AxisValue( controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT ) );
				std::cout << std::endl;
			}

			Uint32 ticks = SDL_GetTicks();
			float fps = (float) elapsedFrames
				/ ( (float) ( ticks - startTime ) / 1000.0f );
			printf( "FPS: %.2f\n", fps );
			printf( "delta: %f\n\n", elapsedTime );
			std::cout << std::endl;
			startTime = ticks;
			elapsedFrames = 0;

			printf( "Game Objects:\t%lu\n", currentScene->gameObjects.size() );
			// TODO figure out how many behaviors there are.
			std::cout << std::endl;
		}

		currentScene->Update( input, elapsedTime );

		// render stuffs
		root->renderOneFrame();
		SDL_GL_SwapWindow( window );

		// update debug info
		elapsedFrames++;
	}
}

bool Gunship::ShutDown()
{
	// destroy Ogre object
	delete root;

	// Close and destroy the window
	SDL_DestroyWindow( window );

	// Clean up
	SDL_Quit();

	return true;
}

Scene* Gunship::CurrentScene()
{
	return currentScene;
}

Scene* Gunship::ResetCurrentScene()
{
	delete currentScene;
	currentScene = new Scene( this, root, renderWindow );
	return currentScene;
}

Scene* Gunship::ResetCurrentScene( std::function< void( Scene& ) > init )
{
	delete currentScene;
	currentScene = new Scene( this, root, renderWindow );
	init( *currentScene );
	return currentScene;
}

std::string Gunship::LoadScript( std::string file )
{
	std::string result;

	char buffer[256];
	SDL_RWops* script = SDL_RWFromFile( file.c_str(), "r" ); // hoo boy this is a leak waiting to happen.

	if ( script == nullptr )
	{
		printf( "Script %s not found! SDL Error: %s\n", file.c_str(), SDL_GetError() );
		SDL_RWclose( script );
		return std::string();
	}

	size_t sentinel = 1;
	do
	{
		memset( buffer, 0, sizeof( buffer ) );
		sentinel = SDL_RWread( script, buffer, sizeof( buffer ) - 1, 1 );
		result += buffer;
	}
	while ( sentinel != 0 );

	SDL_RWclose( script );
	return result;
}

void Gunship::RunStartupScript( const char* file )
{
	// create scope for v8
	v8::Isolate::Scope isolateScope( isolate );
	v8::HandleScope handleScope( isolate );
	v8::Local< v8::Context > context = v8::Local< v8::Context >::New( isolate, _context );
	v8::Context::Scope contextScope( context );

	std::string startup = LoadScript( JS_ROOT_DIR + ( "/" + std::string( file ) ) );
	{
		v8::TryCatch tryCatch;

		v8::Local< v8::Script > script = v8::Script::Compile( V8_STRING( isolate, startup.c_str() ) );
		v8::Local< v8::Value > result = script->Run();
		v8::String::Utf8Value utf8( result );

		if ( tryCatch.HasCaught() )
		{
			printf( "startup script %s failed:\n", file );
			ReportException( isolate, tryCatch );
		}
	}
}

void Gunship::ReportException( v8::Isolate* isolate, v8::TryCatch& try_catch )
{
	v8::HandleScope handle_scope( isolate );
	v8::String::Utf8Value exception( try_catch.Exception() );
	const char* exception_string = *exception;
	v8::Handle< v8::Message > message = try_catch.Message();
	if ( message.IsEmpty() )
	{
		// V8 didn't provide any extra information about this error; just
		// print the exception.
		printf( "%s\n", exception_string );
	}
	else
	{
		// Print (filename):(line number): (message).
		v8::String::Utf8Value filename(
			message->GetScriptOrigin().ResourceName() );
		const char* filename_string = *filename;
		int linenum = message->GetLineNumber();
		printf( "%s:%i: %s\n", filename_string, linenum, exception_string );
		// Print line of source code.
		v8::String::Utf8Value sourceline( message->GetSourceLine() );
		const char* sourceline_string = *sourceline;
		printf( "%s\n", sourceline_string );
		// Print wavy underline (GetUnderline is deprecated).
		int start = message->GetStartColumn();
		for ( int i = 0; i < start; i++ )
		{
			printf( " " );
		}
		int end = message->GetEndColumn();
		for ( int i = start; i < end; i++ )
		{
			printf( "^" );
		}
		printf( "\n" );
	}
}

int main( int argc, char* argv[] )
{
	Gunship gunship;

	// initialize and run the engine
	if ( gunship.InitSystems() )
	{
		gunship.Start();
		gunship.ShutDown();
	}

	return 0;
}

