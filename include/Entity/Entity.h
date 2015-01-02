#pragma once

namespace Gunship
{
	class EntityManager;

	struct Entity
	{
		typedef unsigned int ID;

		ID id;
		EntityManager& manager;

		Entity( ID id, EntityManager& manager );
	};
}
