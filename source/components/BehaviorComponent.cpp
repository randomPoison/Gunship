#include "components/Component.h"

#include "components/BehaviorComponent.h"

BehaviorComponent::BehaviorComponent( BehaviorFunction behavior ) :
	behavior( behavior ),
	id( GenerateUniqueComponentID() )
{
}

Behavior::Behavior( Scene& scene, component_id id, size_t index ) : ComponentLocator( &scene, id, index )
{
}
