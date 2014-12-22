#pragma once

#include <utility>
#include <vector>

#include <entityx/help/NonCopyable.h>

#include "System.h"

namespace Gunship
{
	template< class BaseType >
	class SystemManager : public entityx::help::NonCopyable
	{
	public:
		template< class SystemType, typename ... Args >
		SystemType& Add( Args&& ... args )
		{
			// have the map allocate space for the system
			_systems.emplace_back();

			// get pointer to memory allocated within the map
			BaseType* systemAddress = &_systems.back();

			// re-construct the object with the correct derived type
			SystemType* newSystem =
				new( systemAddress ) SystemType( std::forward< Args >( args ) ... );

			return *newSystem;
		}

		template< typename ... Args >
		void UpdateAll( Args&& ... args )
		{
			for ( BaseType& system : _systems )
			{
				system.Update( std::forward< Args >( args ) ... );
			}
		}

	private:
		std::vector< BaseType > _systems;
	};
}
