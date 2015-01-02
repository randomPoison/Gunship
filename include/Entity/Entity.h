#pragma once

namespace Gunship
{
	class EntityManager;

	struct Entity
	{
		typedef unsigned int ID;

		ID id;
		EntityManager& manager;
	};

	class EntityManager
	{
	public:

	private:
		static Entity::ID _idIndex;
	};
}
