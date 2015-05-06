#pragma once

namespace Gunship
{
	class EntityManager;

	struct Entity
	{
		typedef unsigned int ID;

		operator ID();

		ID id;
	};
}
