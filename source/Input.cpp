#include <iostream>
#include <algorithm>

#include "Input.h"

namespace Gunship
{
	static const float AXIS_MAX = 32768.0f; ///< The maximum value that SDL2 returns for a joystick's position.

	Input::Input()
		: _mouseMovement{ 0, 0 },
		  _mousePos{ 0, 0 },
		  _exit( false )
	{
		// initialize joysticks and whatnot
		if ( SDL_NumJoysticks() > 0 )
		{
			printf( "num joysticks: %d\n", SDL_NumJoysticks() );
			SDL_GameController* controller = SDL_GameControllerOpen( 0 );

			std::cout << "joystick is controller: "
			          << ( SDL_IsGameController( 0 ) ? "true" : "false" )
			          << std::endl;

			if ( controller == nullptr )
			{
				printf( "Warning: Unable to open game controller! SDL Error: %s\n",
				        SDL_GetError() );
				return; // TODO allow Gunship to handle this error better
			}
			_instance->_controllers.push_back( controller );
		}
	}

	void Input::ConsumeInput()
	{
		KeyEvents& keyDownEvents = _instance->_keyDownEvents;
		KeyEvents& keyUpEvents = _instance->_keyUpEvents;
		KeyEvents& downKeys = _instance->_downKeys;
		JoystickEvents& joyAxisEvents = _instance->_joyAxisEvents;

		keyUpEvents.clear();
		joyAxisEvents.clear();

		// reset mouse movement values in case mouse did not move this frame
		_instance->_mouseMovement.x = 0;
		_instance->_mouseMovement.y = 0;

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
			case SDL_MOUSEMOTION:
				_instance->_mouseMovement.x = event.motion.xrel;
				_instance->_mouseMovement.y = event.motion.yrel;
				_instance->_mousePos.x = event.motion.x;
				_instance->_mousePos.y = event.motion.y;
				break;
			}
		}
	}

	bool Input::KeyPressed( SDL_Scancode key )
	{
		KeyEvents& keyDownEvents = _instance->_keyDownEvents;
		return std::find( keyDownEvents.begin(), keyDownEvents.end(), key ) != keyDownEvents.end();
	}

	bool Input::KeyDown( SDL_Scancode key )
	{
		KeyEvents& downKeys = _instance->_downKeys;
		return std::find( downKeys.begin(), downKeys.end(), key ) != downKeys.end();
	}

	float Input::AxisValue( int controller, SDL_GameControllerAxis axis )
	{
		return AxisValue( _instance->_controllers[controller], axis );
	}

	float Input::AxisValue( SDL_GameController* controller, SDL_GameControllerAxis axis )
	{
		float axisValue = SDL_GameControllerGetAxis( controller, axis ) / AXIS_MAX;
		return ( std::abs( axisValue ) > 0.17f ) ? axisValue : 0.0f;
	}

	const Input::ControllerArray& Input::controllers()
	{
		return _instance->_controllers;
	}

	bool Input::exit()
	{
		return _instance->_exit;
	}

	Input::MouseCoord Input::mouseMovement()
	{
		return _instance->_mouseMovement;
	}

	Input::MouseCoord Input::mousePosition()
	{
		return _instance->_mousePos;
	}
}
