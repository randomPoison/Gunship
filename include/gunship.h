#pragma once

#include <SDL.h>
#include <SDL_syswm.h>
#include <iostream>

#include <OgreRoot.h>
#include <OgreManualObject.h>
#include <OgreRenderWindow.h>

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
