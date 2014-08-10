#include "Gunship.h"

#include "Input.h"

bool Input::KeyPressed( SDL_Keycode key ) const
{
	for ( SDL_KeyboardEvent event : keyEvents )
	{
		if ( event.type = SDL_KEYDOWN && event.keysym.sym == key )
		{
			return true;
		}
	}

	return false;
}

void Input::Reset()
{
	keyEvents.empty();
	joyAxisEvents.empty();
}
