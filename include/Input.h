# pragma once

#include <vector>

class Input
{
public:
	std::vector< SDL_KeyboardEvent > keyEvents;

	bool KeyPressed( SDL_Keycode key ) const;
	bool KeyUp( SDL_Keycode key ) const;
};
