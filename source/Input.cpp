#include <iostream>

#include "Input.h"
#include "Utility/VectorHelpers.h"

namespace Gunship
{
	static const float AXIS_MAX = 32768.0f; ///< The maximum value that SDL2 returns for a joystick's position.

	Input::Input()
		: _exit( false )
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
		// retrieve variables from instance
		KeyEvents& pressedKeys = _instance->_pressedKeys;
		KeyEvents& releasedKeys = _instance->_releasedKeys;
		KeyEvents& downKeys = _instance->_downKeys;
		JoystickEvents& joyAxisEvents = _instance->_joyAxisEvents;
		MouseButtonEvents& downMouseButtons = _instance->_downMouseButtons;
		MouseButtonEvents& pressedMouseButtons = _instance->_pressedMouseButtons;
		MouseButtonEvents& releasedMousebuttons = _instance->_releasedMouseButtons;
		MouseCoord& mouseMovement = _instance->_mouseMovement;
		MouseCoord& mousePos = _instance->_mousePos;

		// reset events from last frame
		pressedKeys.clear();
		releasedKeys.clear();
		joyAxisEvents.clear();
		pressedMouseButtons.clear();
		releasedMousebuttons.clear();

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
					pressedKeys.push_back( event.key.keysym.scancode );
				}
				break;
			case SDL_KEYUP:
				VectorHelpers::EraseIfPresent( downKeys, event.key.keysym.scancode );
				releasedKeys.push_back( event.key.keysym.scancode );
				break;
			case SDL_JOYAXISMOTION:
				joyAxisEvents.push_back( event.jaxis );
				break;
			case SDL_MOUSEMOTION:
				mouseMovement.x = event.motion.xrel;
				mouseMovement.y = event.motion.yrel;
				mousePos.x = event.motion.x;
				mousePos.y = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if ( std::find( downMouseButtons.begin(), downMouseButtons.end(), event.button.button ) == downMouseButtons.end() )
				{
					downMouseButtons.push_back( event.button.button );
					pressedMouseButtons.push_back( event.button.button );
				}
				break;
			case SDL_MOUSEBUTTONUP:
				VectorHelpers::EraseIfPresent( downMouseButtons, event.button.button );
				releasedMousebuttons.push_back( event.button.button );
				break;
			}
		}
	}

	bool Input::KeyPressed( SDL_Scancode key )
	{
		KeyEvents& pressedKeys = _instance->_pressedKeys;
		return std::find( pressedKeys.begin(), pressedKeys.end(), key ) != pressedKeys.end();
	}

	bool Input::KeyReleased( SDL_Scancode key )
	{
		KeyEvents& releasedKeys = _instance->_releasedKeys;
		return std::find( releasedKeys.begin(), releasedKeys.end(), key ) != releasedKeys.end();
	}

	bool Input::KeyUp( SDL_Scancode key )
	{
		KeyEvents& downKeys = _instance->_downKeys;
		return std::find( downKeys.begin(), downKeys.end(), key ) == downKeys.end();
	}

	bool Input::KeyDown( SDL_Scancode key )
	{
		KeyEvents& downKeys = _instance->_downKeys;
		return std::find( downKeys.begin(), downKeys.end(), key ) != downKeys.end();
	}

	bool Input::MouseButtonPressed( Uint8 button )
	{
		MouseButtonEvents& pressedMouseButtons = _instance->_pressedMouseButtons;
		return std::find( pressedMouseButtons.begin(), pressedMouseButtons.end(), button ) != pressedMouseButtons.end();
	}

	bool Input::MouseButtonReleased( Uint8 button )
	{
		MouseButtonEvents& releasedMouseButtons = _instance->_releasedMouseButtons;
		return std::find( releasedMouseButtons.begin(), releasedMouseButtons.end(), button ) != releasedMouseButtons.end();
	}

	bool Input::MouseButtonUp( Uint8 button )
	{
		MouseButtonEvents& downMouseButtons = _instance->_downMouseButtons;
		return std::find( downMouseButtons.begin(), downMouseButtons.end(), button ) == downMouseButtons.end();
	}

	bool Input::MouseButtonDown( Uint8 button )
	{
		MouseButtonEvents& downMouseButtons = _instance->_downMouseButtons;
		return std::find( downMouseButtons.begin(), downMouseButtons.end(), button ) != downMouseButtons.end();
	}

	float Input::AxisMotion( Uint8 controller, Uint8 axis )
	{
		JoystickEvents& joyAxisEvents = _instance->_joyAxisEvents;
		auto joyAxis = std::find_if( joyAxisEvents.begin(), joyAxisEvents.end(), [ controller, axis ]( const SDL_JoyAxisEvent& joyAxisEvent )
		{
			return joyAxisEvent.which == controller && joyAxisEvent.axis == axis;
		} );
		return ( joyAxis != joyAxisEvents.end() ? joyAxis->value / AXIS_MAX : 0.0f );
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
