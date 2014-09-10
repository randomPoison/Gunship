# pragma once

class Gunship;

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
	void Update( Gunship* gunship );

	bool KeyPressed( SDL_Scancode key ) const;
	bool KeyReleased( SDL_Scancode key ) const;
	bool KeyUp( SDL_Scancode key ) const;
	bool KeyDown( SDL_Scancode key ) const;

	float AxisMotion( Uint8 controller, Uint8 axis ) const;
	float AxisValue( int controller, SDL_GameControllerAxis axis ) const;
	float AxisValue( SDL_GameController*, SDL_GameControllerAxis axis ) const;
};
