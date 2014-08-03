#include <SDL.h>
#include <SDL_syswm.h>
#include <iostream>

#include <OgreRoot.h>
#include <OgreManualObject.h>
#include <OgreRenderWindow.h>

// temporary includes for createColourCube()
#include <OgreMeshManager.h>
#include <OgreHardwareBufferManager.h>
#include <OgreSubMesh.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include "Gunship.h"
#include "Scene.h"

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
	const size_t vbufCount = 3*2*nVertices;
	float vertices[vbufCount] = {
		-1.0,1.0,-1.0,				//0 position
		-sqrt13,sqrt13,-sqrt13,		//0 normal
		1.0,1.0,-1.0,				//1 position
		sqrt13,sqrt13,-sqrt13,		//1 normal
		1.0,-1.0,-1.0,				//2 position
		sqrt13,-sqrt13,-sqrt13,		//2 normal
		-1.0,-1.0,-1.0,				//3 position
		-sqrt13,-sqrt13,-sqrt13,	//3 normal
		-1.0,1.0,1.0,				//4 position
		-sqrt13,sqrt13,sqrt13,		//4 normal
		1.0,1.0,1.0,				//5 position
		sqrt13,sqrt13,sqrt13,		//5 normal
		1.0,-1.0,1.0,				//6 position
		sqrt13,-sqrt13,sqrt13,		//6 normal
		-1.0,-1.0,1.0,				//7 position
		-sqrt13,-sqrt13,sqrt13,		//7 normal
	};

	RenderSystem* rs = Root::getSingleton().getRenderSystem();
	RGBA colours[nVertices];
	RGBA *pColour = colours;
	// Use render system to convert colour value since colour packing varies
	rs->convertColourValue(ColourValue(1.0,0.0,0.0), pColour++); //0 colour
	rs->convertColourValue(ColourValue(1.0,1.0,0.0), pColour++); //1 colour
	rs->convertColourValue(ColourValue(0.0,1.0,0.0), pColour++); //2 colour
	rs->convertColourValue(ColourValue(0.0,0.0,0.0), pColour++); //3 colour
	rs->convertColourValue(ColourValue(1.0,0.0,1.0), pColour++); //4 colour
	rs->convertColourValue(ColourValue(1.0,1.0,1.0), pColour++); //5 colour
	rs->convertColourValue(ColourValue(0.0,1.0,1.0), pColour++); //6 colour
	rs->convertColourValue(ColourValue(0.0,0.0,1.0), pColour++); //7 colour

	/// Define 12 triangles (two triangles per cube face)
	/// The values in this table refer to vertices in the above table
	const size_t ibufCount = 36;
	unsigned short faces[ibufCount] = {
		0,2,3,
		0,1,2,
		1,6,2,
		1,5,6,
		4,6,5,
		4,7,6,
		0,7,4,
		0,3,7,
		0,5,1,
		0,4,5,
		2,7,3,
		2,6,7
	};

	/// Create vertex data structure for 8 vertices shared between submeshes
	msh->sharedVertexData = new VertexData();
	msh->sharedVertexData->vertexCount = nVertices;

	/// Create declaration (memory format) of vertex data
	VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
	size_t offset = 0;
	// 1st buffer
	decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
	offset += VertexElement::getTypeSize(VET_FLOAT3);
	decl->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
	offset += VertexElement::getTypeSize(VET_FLOAT3);
	/// Allocate vertex buffer of the requested number of vertices (vertexCount) 
	/// and bytes per vertex (offset)
	HardwareVertexBufferSharedPtr vbuf = 
		HardwareBufferManager::getSingleton().createVertexBuffer(
		offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	/// Upload the vertex data to the card
	vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);

	/// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
	VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding; 
	bind->setBinding(0, vbuf);

	// 2nd buffer
	offset = 0;
	decl->addElement(1, offset, VET_COLOUR, VES_DIFFUSE);
	offset += VertexElement::getTypeSize(VET_COLOUR);
	/// Allocate vertex buffer of the requested number of vertices (vertexCount) 
	/// and bytes per vertex (offset)
	vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(
		offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	/// Upload the vertex data to the card
	vbuf->writeData(0, vbuf->getSizeInBytes(), colours, true);

	/// Set vertex buffer binding so buffer 1 is bound to our colour buffer
	bind->setBinding(1, vbuf);

	/// Allocate index buffer of the requested number of vertices (ibufCount) 
	HardwareIndexBufferSharedPtr ibuf = HardwareBufferManager::getSingleton().
		createIndexBuffer(
		HardwareIndexBuffer::IT_16BIT, 
		ibufCount, 
		HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	/// Upload the index data to the card
	ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);

	/// Set parameters of the submesh
	sub->useSharedVertices = true;
	sub->indexData->indexBuffer = ibuf;
	sub->indexData->indexCount = ibufCount;
	sub->indexData->indexStart = 0;

	/// Set bounding information (for culling)
	msh->_setBounds(AxisAlignedBox(-100,-100,-100,100,100,100));
	msh->_setBoundingSphereRadius(Math::Sqrt(3*100*100));

	/// Notify -Mesh object that it has been loaded
	msh->load();

	MaterialPtr material = MaterialManager::getSingleton().create(
		"Test/ColourTest", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	material->getTechnique(0)->getPass(0)->setVertexColourTracking(TVC_AMBIENT);
}

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

	// initialize primitive meshes
	createColourCube();

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

Scene* Gunship::ResetCurrentScene( std::function< void( Scene& ) > init )
{
	delete currentScene;
	currentScene = new Scene( root, renderWindow );
	init( *currentScene );
	return currentScene;
}
