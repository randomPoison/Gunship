#include "components/Component.h"

component_id GenerateUniqueComponentID()
{
	static size_t nextID = 1;
	return nextID++;
}
