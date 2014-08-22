#include "Gunship.h"
#include "Components/Behavior.h"

Behavior::Behavior( Scene& scene, component_id id, size_t index ) : ComponentLocator( &scene, id, index )
{
}

void Behavior::Destroy()
{
	scene->MarkForDestroy( *this );
}
