#include <iostream>

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

float Input::AxisMotion( SDL_JoystickID joystick, Uint8 axis ) const
{
	for ( SDL_JoyAxisEvent event : joyAxisEvents )
	{
		if ( event.which == joystick && event.axis == axis )
		{
			return (float)event.value / AXIS_MAX;
		}
	}

	return 0.0f;
}

float Input::AxisValue( int joystick, Uint8 axis ) const
{
	float axisValue = SDL_JoystickGetAxis( joysticks[joystick], axis ) / AXIS_MAX;
	return ( fabs( axisValue ) > 0.17f ) ? axisValue : 0.0f;
}
