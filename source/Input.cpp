#include <iostream>
#include <cmath>

#include "Engine.h"
#include "Input.h"

static const float AXIS_MAX = 32768.0f; ///< The maximum value that SDL2 returns for a joystick's position.

Gunship::Input::Input() : exit( false )
{
}

void Gunship::Input::ConsumeInput()
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

void Gunship::Input::Update( Engine* engine )
{
}

bool Gunship::Input::KeyPressed( SDL_Scancode key ) const
{
	return std::find( keyDownEvents.begin(), keyDownEvents.end(), key ) != keyDownEvents.end();
}

float Gunship::Input::AxisValue( int controller, SDL_GameControllerAxis axis ) const
{
	return AxisValue( controllers[controller], axis );
}

float Gunship::Input::AxisValue( SDL_GameController* controller, SDL_GameControllerAxis axis ) const
{
	float axisValue = SDL_GameControllerGetAxis( controller, axis ) / AXIS_MAX;
	return ( std::abs( axisValue ) > 0.17f ) ? axisValue : 0.0f;
}
