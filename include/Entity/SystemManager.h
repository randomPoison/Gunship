#pragma once

#include <utility>
#include <memory>        ///< @todo remove dependency on STL containers.
#include <vector>        ///< @todo remove dependency on STL containers.
#include <unordered_map> ///< @todo remove dependency on STL containers.

#include "Utility/NonCopyable.h"

#include "System.h"

namespace Gunship
{
	template < class BaseType >
	class SystemManager : public NonCopyable
	{
	public:
		template < class SystemType, typename... Args >
		std::shared_ptr< SystemType > Add( Args&&... args )
		{
			std::shared_ptr< SystemType > systemPointer(
				new SystemType( std::forward< Args >( args )... ) );
			_systems.push_back( systemPointer );
			_indices[SystemType::id()] = _systems.size() - 1;
			return systemPointer;
		}

		template < typename... Args >
		void UpdateAll( Args&&... args )
		{
			for ( std::shared_ptr<BaseType>& system : _systems )
			{
				if ( system->active )
				{
					system->Update( std::forward< Args >( args ) ... );
				}
			}
		}

		template < typename SystemType >
		SystemType& Get()
		{
			static_cast< SystemType& >( _systems[_indices[SystemType::id()]] );
		}

		template < typename SystemType >
		void Remove()
		{
			// Retrieve the index of the system, then remove the system
			// from the index map.
			auto iterator = _indices.find( SystemType::id() );
			size_t index = iterator->second;
			_indices->erase( iterator );

			// Remove the system from the list of systems.
			_systems.erase( _systems.begin() + index );
		}

		template < typename SystemType >
		void Disable()
		{
			_systems[_indices[SystemType::id()]].active = false;
		}

		template < typename SystemType >
		void Enable()
		{
			_systems[_indices[SystemType::id()]].active = true;
		}

	private:
		std::vector< std::shared_ptr< BaseType > > _systems;
		std::unordered_map< SystemBase::ID, size_t > _indices;
	};
}
