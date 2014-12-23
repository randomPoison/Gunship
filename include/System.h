#pragma once

#include <SDL_stdinc.h>
#include <entityx/help/NonCopyable.h>

namespace entityx
{
	class EntityManager;
}

namespace Gunship
{
	/**
	 * @brief The base class for all Gunship systems.
	 *
	 * @details
	 *     SystemBase defines the type Family and the variable familyCounter,
	 *     which are used to give each System a unique identity. This is
	 *     currently not put to use within Gunship, but is maintained for
	 *     the purposed of compatibility with other EntityX systems, and may
	 *     be utilized in the future.
	 */
	class SystemBase : public entityx::help::NonCopyable
	{
	public:
		typedef Uint32 Family;

		virtual ~SystemBase();

		static Family familyCounter;
	};

	class DefaultSystemBase : SystemBase
	{
	public:
		virtual void Update( entityx::EntityManager& entities ) = 0;
	};

	template< class Derived, class Base = DefaultSystemBase >
	class System : public Base
	{
	private:
		template< class BaseType >
		friend class SystemManager;

		static SystemBase::Family family()
		{
			static SystemBase::Family family = SystemBase::familyCounter++;
			return family;
		}
	};

	class BehaviorSystemBase : SystemBase
	{
	public:
		virtual void Update( entityx::EntityManager& entities, float delta ) = 0;
	};
}
