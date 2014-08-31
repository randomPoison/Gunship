#pragma once

#define V8_ENTER_SCOPE()	v8::Isolate* isolate = v8::Isolate::GetCurrent();\
							v8::Isolate::Scope isolateScope( isolate );\
							v8::HandleScope handleScope( isolate );
