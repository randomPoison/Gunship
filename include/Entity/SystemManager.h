#pragma once

#include <utility>
#include <memory> // TODO remove dependency on STL containers
#include <vector> // TODO remove dependency on STL containers

#include "Utility/NonCopyable.h"

#include "System.h"

namespace Gunship
{
	template< class BaseType >
	class SystemManager : public NonCopyable
	{
	public:
		template< class SystemType, typename ... Args >
		std::shared_ptr< SystemType > Add( Args&& ... args )
		{
			std::shared_ptr< SystemType > systemPointer(
				new SystemType( std::forward< Args >( args ) ... ) );
			_systems.push_back( systemPointer );
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
		std::vector< std::shared_ptr< BaseType > > _systems;
	};
}
