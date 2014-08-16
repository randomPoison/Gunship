#include "Gunship.h"
#include "components/BehaviorComponent.h"

BehaviorComponent::BehaviorComponent( GameObject& owner, BehaviorFunction behavior ) :
	behavior( behavior ),
	id( GenerateUniqueComponentID() ),
	ownerId( owner.id )
{
}

Behavior::Behavior( Scene& scene, component_id id ) : ComponentLocator( &scene, id )
{
}
