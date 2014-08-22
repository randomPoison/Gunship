#include "Gunship.h"
#include "Components\ComponentLocator.h"

ComponentLocator::ComponentLocator( Scene* scene, component_id id, size_t index ) :
	scene( scene ),
	id( id ),
	index( index )
{
}

bool operator==( const ComponentLocator& first, const ComponentLocator& second )
{
	return first.id == second.id;
}
