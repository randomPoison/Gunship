#pragma once

#include <utility>
#include <memory>

#include <entityx/help/NonCopyable.h>

#include "System.h"
#include "Containers/Array.h"
#include "Memory/MemoryTypes.h"

namespace Gunship
{
	extern Memory::Allocator* gDefaultAllocator;

	template< class BaseType >
	class SystemManager : public entityx::help::NonCopyable
	{
	public:
		SystemManager()
			: _systems( gDefaultAllocator, 100 )
		{
		}

		template< class SystemType, typename ... Args >
		std::shared_ptr< SystemType > Add( Args&& ... args )
		{
			std::shared_ptr< SystemType > systemPointer(
				new SystemType( std::forward< Args >( args ) ... ) );
			_systems.PushBack( systemPointer );
			return systemPointer;
		}

		template< typename ... Args >
		void UpdateAll( Args&& ... args )
		{
			for ( std::shared_ptr<BaseType>& system : _systems )
			{
				system->Update( std::forward< Args >( args ) ... );
			}
		}

	private:
		Array< std::shared_ptr< BaseType > > _systems;
	};
}
