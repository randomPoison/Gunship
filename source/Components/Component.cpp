#include "Gunship.h"
#include "Components/Component.h"

Component::Component( GameObject& owner ) :
	owner( owner ),
	id( GenerateUniqueComponentID() )
{
}

component_id Component::GenerateUniqueComponentID()
{
	static component_id nextID = 1;
	return nextID++;
}

bool operator==( const Component& first, const Component& second )
{
	return first.id == second.id;
}