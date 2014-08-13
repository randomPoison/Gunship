# pragma once

#include <vector>

class Input
{
public:
	bool exit = false;

	void ConsumeInput();

	bool KeyPressed( SDL_Keycode key ) const;
	bool KeyReleased( SDL_Keycode key ) const;
	bool KeyUp( SDL_Keycode key ) const;
	bool KeyDown( SDL_Keycode key ) const;

	float AxisMotion( SDL_JoystickID joystick, Uint8 axis ) const;
	float AxisValue( SDL_JoystickID joystick, Uint8 axis ) const;

private:
	std::vector< SDL_Keycode > downKeys;
	std::vector< SDL_Joystick* > joysticks;

	std::vector< SDL_Keycode > keyDownEvents;
	std::vector< SDL_Keycode > keyUpEvents;
	std::vector< SDL_JoyAxisEvent > joyAxisEvents;

	friend class Gunship;
};
