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
			int x = 0;
			int y = 0;
		};

		typedef std::vector< SDL_Scancode > KeyEvents;
		typedef std::vector< SDL_GameController* > ControllerArray;
		typedef std::vector< SDL_JoyAxisEvent > JoystickEvents;
		typedef std::vector< Uint8 > MouseButtonEvents;

		static void ConsumeInput();

		static bool KeyPressed( SDL_Scancode key );
		static bool KeyReleased( SDL_Scancode key );
		static bool KeyUp( SDL_Scancode key );
		static bool KeyDown( SDL_Scancode key );

		static bool MouseButtonPressed( Uint8 button );
		static bool MouseButtonReleased( Uint8 button );
		static bool MouseButtonUp( Uint8 button );
		static bool MouseButtonDown( Uint8 button );

		/**
		 * @brief Return the motion of the joystick this frame.
		 *
		 * @details
		 *     This method returns the amount the joystick in the last frame,
		 *     NOT the joystick's current position. If you want the current value
		 *     of the axis, call AxisValue().
		 */
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

		MouseButtonEvents _downMouseButtons;
		MouseButtonEvents _pressedMouseButtons;
		MouseButtonEvents _releasedMouseButtons;

		MouseCoord _mouseMovement;
		MouseCoord _mousePos;

		bool _exit;

		Input();
	};
}
