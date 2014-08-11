#include "Gunship.h"

#include "Input.h"

static const float AXIS_MAX = 32768.0f;

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
	return ( abs( axisValue ) > 0.3f ) ? axisValue : 0.0f;
}

void Input::Reset()
{
	keyEvents.clear();
	joyAxisEvents.clear();
}
