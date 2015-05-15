#pragma once

#include <SDL_stdinc.h>
#include <Utility/NonCopyable.h>

namespace entityx
{
	class EntityManager;
}

namespace Gunship
{
	class Scene;

	/// @brief The base class for all Gunship systems.
	///
	/// @details
	///     SystemBase defines the type Family and the variable idCounter,
	///     which are used to give each System a unique identity.
	class SystemBase : public NonCopyable
	{
	public:
		typedef Uint32 ID;

		static ID idCounter;

		bool active;

		SystemBase();

		virtual ~SystemBase();
	};

	class DefaultSystemBase : public SystemBase
	{
	public:
		virtual void Update( Scene& scene, float delta ) = 0;
	};

	template< class Derived, class Base = DefaultSystemBase >
	class System : public Base
	{
	private:
		template< class BaseType >
		friend class SystemManager;

		static SystemBase::ID id()
		{
			static SystemBase::ID id = SystemBase::idCounter++;
			return id;
		}
	};

	class BehaviorSystemBase : public SystemBase
	{
	public:
		virtual void Update( Scene& scene, float delta ) = 0;
	};
}
