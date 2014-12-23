#include <algorithm>

#include "Input.h"

static const float AXIS_MAX = 32768.0f; ///< The maximum value that SDL2 returns for a joystick's position.

Gunship::Input::Input()
	: _exit( false )
{
}

void Gunship::Input::ConsumeInput()
{
	KeyEvents& keyDownEvents = _instance->_keyDownEvents;
	KeyEvents& keyUpEvents = _instance->_keyUpEvents;
	KeyEvents& downKeys = _instance->_downKeys;
	JoystickEvents& joyAxisEvents = _instance->_joyAxisEvents;


	keyUpEvents.clear();
	joyAxisEvents.clear();

	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type )
		{
		case SDL_QUIT:
			_instance->_exit = true;
			break;
		case SDL_KEYDOWN:
			if ( std::find( downKeys.begin(), downKeys.end(), event.key.keysym.scancode ) == downKeys.end() )
			{
				downKeys.push_back( event.key.keysym.scancode );
				keyDownEvents.push_back( event.key.keysym.scancode );
			}
			break;
		case SDL_KEYUP:
			downKeys.erase( std::find( downKeys.begin(), downKeys.end(), event.key.keysym.scancode ) );
			keyUpEvents.push_back( event.key.keysym.scancode );
			break;
		case SDL_JOYAXISMOTION:
			joyAxisEvents.push_back( event.jaxis );
			break;
		}
	}
}

bool Gunship::Input::KeyPressed( SDL_Scancode key )
{
	KeyEvents& keyDownEvents = _instance->_keyDownEvents;
	return std::find( keyDownEvents.begin(), keyDownEvents.end(), key ) != keyDownEvents.end();
}

float Gunship::Input::AxisValue( int controller, SDL_GameControllerAxis axis )
{
	return AxisValue( _instance->_controllers[controller], axis );
}

float Gunship::Input::AxisValue( SDL_GameController* controller, SDL_GameControllerAxis axis )
{
	float axisValue = SDL_GameControllerGetAxis( controller, axis ) / AXIS_MAX;
	return ( std::abs( axisValue ) > 0.17f ) ? axisValue : 0.0f;
}

Gunship::Input::ControllerArray& Gunship::Input::controllers()
{
	return _instance->_controllers;
}

bool Gunship::Input::exit()
{
	return _instance->_exit;
}
