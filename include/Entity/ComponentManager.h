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
