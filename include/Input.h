# pragma once

#include <vector>

class Input
{
public:
	std::vector< SDL_Keycode > keys;
	std::vector< SDL_Joystick* > joysticks;

	std::vector< SDL_KeyboardEvent > keyEvents;
	std::vector< SDL_JoyAxisEvent > joyAxisEvents;

	bool KeyPressed( SDL_Keycode key ) const;
	bool KeyUp( SDL_Keycode key ) const;

	float AxisMotion( SDL_JoystickID joystick, Uint8 axis ) const;
	float AxisValue( SDL_JoystickID joystick, Uint8 axis ) const;

	void Reset();
};
