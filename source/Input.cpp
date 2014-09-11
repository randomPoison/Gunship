#include <iostream>
#include <cmath>

#include "Gunship.h"
#include "Input.h"

static const float AXIS_MAX = 32768.0f;

Input::Input() : exit( false )
{
}

void Input::ConsumeInput()
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

void Input::Update( Gunship* gunship )
{
	// enter v8 scope
	v8::Isolate* isolate = gunship->isolate;
	v8::Isolate::Scope isolateScope( isolate );
	v8::HandleScope handleScope( isolate );
	v8::Local< v8::Context > context = v8::Local< v8::Context >::New( isolate, gunship->_context );
	v8::Context::Scope contextScope( context );

	// down keys array
	v8::Local< v8::Array > _downKeys = V8_ARRAY( isolate, downKeys.size() );
	V8_FILL_ARRAY_FROM_VECTOR( _downKeys, downKeys, V8_INTEGER );

	// pressed keys array
	v8::Local< v8::Array > _pressedKeys = V8_ARRAY( isolate, keyDownEvents.size() );
	V8_FILL_ARRAY_FROM_VECTOR( _pressedKeys, keyDownEvents, V8_INTEGER );

	// released keys array
	v8::Local< v8::Array > _releasedKeys = V8_ARRAY( isolate, keyUpEvents.size() );
	V8_FILL_ARRAY_FROM_VECTOR( _releasedKeys, keyUpEvents, V8_INTEGER );

	v8::Local< v8::Object > _gunship = context->Global()->Get( V8_STRING( isolate, "Gunship" ) )->ToObject();
	v8::Local< v8::Function > callback = _gunship->ToObject()->Get( V8_STRING( isolate, "UpdateInput" ) ).As< v8::Function >();

	// create args
	v8::Local< v8::Value > args[] = { v8::Object::New( isolate ) };
	args[0]->ToObject()->Set( V8_STRING( isolate, "down" ), _downKeys );
	args[0]->ToObject()->Set( V8_STRING( isolate, "pressed" ), _pressedKeys );
	args[0]->ToObject()->Set( V8_STRING( isolate, "released" ), _releasedKeys );

	callback->Call( _gunship, 1, args );
}

bool Input::KeyPressed( SDL_Scancode key ) const
{
	return std::find( keyDownEvents.begin(), keyDownEvents.end(), key ) != keyDownEvents.end();
}

float Input::AxisValue( int controller, SDL_GameControllerAxis axis ) const
{
	return AxisValue( controllers[controller], axis );
}

float Input::AxisValue( SDL_GameController* controller, SDL_GameControllerAxis axis ) const
{
	float axisValue = SDL_GameControllerGetAxis( controller, axis ) / AXIS_MAX;
	return ( std::abs( axisValue ) > 0.17f ) ? axisValue : 0.0f;
}
