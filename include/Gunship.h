#pragma once

#include <vector>

// forward declarations because reasons
namespace Ogre {
	class Root;
	class RenderWindow;
};
struct SDL_Window;

class Scene;

class Gunship
{
private:
	// Variables and stuffs
	SDL_Window* window;
	Ogre::Root* root;
	Ogre::RenderWindow* renderWindow;

	void UpdateComponents();

	Scene* currentScene;

public:
	// default constructor
	Gunship();

	~Gunship();

	// initialization and shutdown functions
	bool InitSystems();
	bool Configure();
	void Start();

	bool ShutDown();

	// other functions
	Scene* CurrentScene();
	Scene* ResetCurrentScene();
	Scene* ResetCurrentScene( std::function< void( Scene& ) > );
};
