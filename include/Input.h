# pragma once

struct Input
{
	bool KeyPressed( SDL_Keycode key ) const;
	bool KeyReleased( SDL_Keycode key ) const;
	bool KeyUp( SDL_Keycode key ) const;
	bool KeyDown( SDL_Keycode key ) const;

	float AxisMotion( Uint8 controller, Uint8 axis ) const;
	float AxisValue( int controller, SDL_GameControllerAxis axis ) const;
	float AxisValue( SDL_GameController*, SDL_GameControllerAxis axis ) const;

	bool exit;

	Input();

	void ConsumeInput();

	std::vector< SDL_Keycode > downKeys;
	std::vector< SDL_GameController* > controllers;

	std::vector< SDL_Keycode > keyDownEvents;
	std::vector< SDL_Keycode > keyUpEvents;
	std::vector< SDL_JoyAxisEvent > joyAxisEvents;
};
