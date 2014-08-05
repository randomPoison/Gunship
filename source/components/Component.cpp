#include "Gunship.h"

#include "components/Component.h"

component_id GenerateUniqueComponentID()
{
	static component_id nextID = 1;
	return nextID++;
}

ComponentLocator::ComponentLocator( Scene* scene, component_id id, size_t index ) :
	scene( scene ),
	id( id ),
	index( index )
{
}
