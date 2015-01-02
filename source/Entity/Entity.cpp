#include "Entity/Entity.h"

namespace Gunship
{
	Entity::Entity( ID id, EntityManager& manager )
		: id( id ),
		  manager( manager )
	{
	}
}
