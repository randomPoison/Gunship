#include "Gunship.h"
#include "Components/Collider.h"

Collider::Collider( Scene& scene, component_id id, size_t index ) :
	ComponentLocator( &scene, id, index )
{
}

void Collider::Destroy()
{
}
