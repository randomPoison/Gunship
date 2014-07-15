#pragma once

namespace Ogre {
	class Root;
	class RenderWindow;
};
struct SDL_Window;


class Gunship
{
	// Variables and stuffs
	SDL_Window* window;
	Ogre::Root* root;
	Ogre::RenderWindow* render;

	// initialization functions
	bool InitRenderingSystems( SDL_Window* window, Ogre::Root* root, Ogre::RenderWindow* render );

public:
	// default constructor
	Gunship();
};
