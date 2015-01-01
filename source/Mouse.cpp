#include <SDL_mouse.h>

#include "Mouse.h"

namespace Gunship
{
	void Mouse::SetRelativeMode( bool relativeMode )
	{
		SDL_SetRelativeMouseMode( static_cast< SDL_bool >( relativeMode ) );
	}

	bool Mouse::GetRelativeMode()
	{
		return SDL_GetRelativeMouseMode();
	}
}
