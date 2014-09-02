#pragma once

struct BehaviorComponent : public Component
{
	V8_COPYABLE_PERSISTENT(v8::Object) object;
	V8_COPYABLE_PERSISTENT(v8::Function) function;

	BehaviorComponent( V8_COPYABLE_PERSISTENT(v8::Object) obj, V8_COPYABLE_PERSISTENT(v8::Function) func );
};
