# pragma once

#include <SDL_keycode.h>
#include <SDL_keyboard.h>
#include <SDL_joystick.h>
#include <SDL_gamecontroller.h>
#include <SDL_events.h>

namespace Gunship
{
	class Engine;

	struct Input
	{
		std::vector< SDL_Scancode > downKeys;
		std::vector< SDL_GameController* > controllers;

		std::vector< SDL_Scancode > keyDownEvents;
		std::vector< SDL_Scancode > keyUpEvents;
		std::vector< SDL_JoyAxisEvent > joyAxisEvents;

		bool exit;

		Input();

		void ConsumeInput();
		void Update( Engine* gunship );

		bool KeyPressed( SDL_Scancode key ) const;
		bool KeyReleased( SDL_Scancode key ) const;
		bool KeyUp( SDL_Scancode key ) const;
		bool KeyDown( SDL_Scancode key ) const;

		float AxisMotion( Uint8 controller, Uint8 axis ) const;
		float AxisValue( int controller, SDL_GameControllerAxis axis ) const;
		float AxisValue( SDL_GameController*, SDL_GameControllerAxis axis ) const;
	};
}
