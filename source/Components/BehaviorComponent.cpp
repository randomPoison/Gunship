#include "Gunship.h"
#include "Components/BehaviorComponent.h"

BehaviorComponent::BehaviorComponent( V8_COPYABLE_PERSISTENT(v8::Object) obj, V8_COPYABLE_PERSISTENT(v8::Function) func ) :
	Component::Component(),
	object( obj ),
	function( func )
{
}
