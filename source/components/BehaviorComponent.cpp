#include "Gunship.h"

#include "components/BehaviorComponent.h"

BehaviorComponent::BehaviorComponent( GameObject& owner, BehaviorFunction behavior ) :
	ownerId( owner.id ),
	behavior( behavior ),
	id( GenerateUniqueComponentID() )
{
}

Behavior::Behavior( Scene& scene, component_id id, size_t index ) : ComponentLocator( &scene, id, index )
{
}
