#pragma once

#include "Utility/NonCopyable.h"

namespace Gunship
{
	class ComponentManagerBase : NonCopyable
	{
	public:
		/**
		 * @brief A type used for identifying Component managers.
		 *
		 * @details
		 *     Every ComponentManager is uniquely identified by an ID.
		 *     This ID is used internally by Gunship to manage instances
		 *     of the ComponentManager at runtime.
		 */
		typedef unsigned int ID;

		virtual ~ComponentManagerBase() = default;

	protected:
		static ID _familyCounter;

		/**
		 * @brief Destroys all components marked for destruction.
		 *
		 * @details
		 *     This is to be overridden with implementation-specific
		 *     for the given component mangaer. This is only necessary
		 *     to ensure that all component managers support deferred destruction.
		 */
		virtual void DestroyAllMarked() = 0;

		friend class Scene;
	};

	template< typename Derived >
	class ComponentManager : public ComponentManagerBase
	{
	public:
		static ID id()
		{
			static ID _family = _familyCounter++;
			return _family;
		}
	};
}
