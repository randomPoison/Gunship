#include <iostream>
#include <cmath>

#include "Gunship.h"

#include "Input.h"

static const float AXIS_MAX = 32768.0f;

void Input::ConsumeInput()
{
	keyDownEvents.clear();
	keyUpEvents.clear();
	joyAxisEvents.clear();

	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type )
		{
		case SDL_QUIT:
			exit = true;
			break;
		case SDL_KEYDOWN:
			if ( std::find( downKeys.begin(), downKeys.end(), event.key.keysym.sym ) == downKeys.end() )
			{
				downKeys.push_back( event.key.keysym.sym );
				keyDownEvents.push_back( event.key.keysym.sym );
			}
			break;
		case SDL_KEYUP:
			downKeys.erase( std::find( downKeys.begin(), downKeys.end(), event.key.keysym.sym ) );
			keyUpEvents.push_back( event.key.keysym.sym );
			break;
		case SDL_JOYAXISMOTION:
			joyAxisEvents.push_back( event.jaxis );
			break;
		}
	}
}

bool Input::KeyPressed( SDL_Keycode key ) const
{
	return std::find( keyDownEvents.begin(), keyDownEvents.end(), key ) != keyDownEvents.end();
}

float Input::AxisValue( int controller, SDL_GameControllerAxis axis ) const
{
	return AxisValue( controllers[controller], axis );
}

float Input::AxisValue( SDL_GameController* controller, SDL_GameControllerAxis axis ) const
{
	float axisValue = SDL_GameControllerGetAxis( controller, axis ) / AXIS_MAX;
	return ( std::abs( axisValue ) > 0.17f ) ? axisValue : 0.0f;
}
