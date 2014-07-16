#pragma once

// forward declarations because reasons
namespace Ogre {
	class Root;
	class RenderWindow;
};
struct SDL_Window;

class Gunship
{
private:
	// Variables and stuffs
	SDL_Window* window;
	Ogre::Root* root;
	Ogre::RenderWindow* render;

	void UpdateComponents();

public:
	// default constructor
	Gunship();

	// initialization functions
	bool InitSystems();
	bool Configure();
	void Start();

	bool ShutDown();
};
