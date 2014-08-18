#include "Gunship.h"
#include "components/BehaviorComponent.h"

BehaviorComponent::BehaviorComponent( GameObject& owner, BehaviorFunction behavior ) :
	behavior( behavior ),
	id( GenerateUniqueComponentID() ),
	owner( owner )
{
}

Behavior::Behavior( Scene& scene, component_id id, size_t index ) : ComponentLocator( &scene, id, index )
{
}

void Behavior::Destroy()
{
	scene->MarkForDestroy( *this );
}

bool operator==( const Behavior& first, const Behavior& second )
{
	return first.id == second.id;
}