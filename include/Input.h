# pragma once

#include <vector>

#include <SDL_keycode.h>
#include <SDL_keyboard.h>
#include <SDL_joystick.h>
#include <SDL_gamecontroller.h>
#include <SDL_events.h>

#include "Utility/Singleton.h"

namespace Gunship
{
	class Engine;

	class Input : public Singleton< Input >
	{
	public:
		struct MouseCoord
		{
			int x, y;
		};

		typedef std::vector< SDL_Scancode > KeyEvents;
		typedef std::vector< SDL_GameController* > ControllerArray;
		typedef std::vector< SDL_JoyAxisEvent > JoystickEvents;

		static void ConsumeInput();

		static bool KeyPressed( SDL_Scancode key );
		static bool KeyReleased( SDL_Scancode key );
		static bool KeyUp( SDL_Scancode key );
		static bool KeyDown( SDL_Scancode key );

		static float AxisMotion( Uint8 controller, Uint8 axis );
		static float AxisValue( int controller,
		                        SDL_GameControllerAxis axis );
		static float AxisValue( SDL_GameController*,
		                        SDL_GameControllerAxis axis );

		static const ControllerArray& controllers();
		static bool exit();

		static MouseCoord mouseMovement();
		static MouseCoord mousePosition();

	private:
		friend class Singleton< Input >;

		KeyEvents _downKeys;
		KeyEvents _keyDownEvents;
		KeyEvents _keyUpEvents;
		ControllerArray _controllers;
		JoystickEvents _joyAxisEvents;

		MouseCoord _mouseMovement;
		MouseCoord _mousePos;

		bool _exit;

		Input();
	};
}
