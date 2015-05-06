#pragma once

#include "Entity/Entity.h"
#include "Utility/NonCopyable.h"

namespace Gunship
{
	class ComponentManagerBase : NonCopyable
	{
	public:
		/// @brief A type used for identifying Component managers.
		///
		/// @details
		///     Every ComponentManager is uniquely identified by an ID.
		///     This ID is used internally by Gunship to manage instances
		///     of the ComponentManager at runtime.
		typedef unsigned int ID;

		static ID _familyCounter;

		virtual ~ComponentManagerBase() = default;

		/// @brief Destroys all components marked for destruction.
		///
		/// @details
		///     This is to be overridden with implementation-specific
		///     for the given component mangaer. This is only necessary
		///     to ensure that all component managers support deferred destruction.
		virtual void DestroyAllMarked() = 0;

		/// @brief Destroy all components associated with the specified entity.
		///
		/// @details
		///     This is called automatically by EntityManager when an entity
		///     is destroyed. This is to ensure that no components remain alive
		///     once an entity is destroyed.
		virtual void DestroyAll( Entity::ID entityID ) = 0;
	};

	template< typename Derived >
	class ComponentManager : public ComponentManagerBase
	{
	public:

		/// @brief Provides a unique identifier for this class.
		///
		/// @details
		///     This class allows objects inheriting from ComponentManager
		///     to by grouped by class at runtime by providing an ID value
		///     that is unique to that class.
		static ID id()
		{
			static ID _family = _familyCounter++;
			return _family;
		}
	};
}
