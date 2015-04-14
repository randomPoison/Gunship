#pragma once

#include <utility>
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
		~SystemManager< BaseType >()
		{
			for ( BaseType* base : _systems )
			{
				delete base;
			}
		}

		template < class SystemType, typename... Args >
		SystemType* Add( Args&&... args )
		{
			SystemType* system = new SystemType( std::forward< Args >( args )... );
			_systems.push_back( system );
			_indices[SystemType::id()] = _systems.size() - 1;
			return system;
		}

		template < typename... Args >
		void UpdateAll( Args&&... args )
		{
			for ( BaseType* system : _systems )
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
			return *static_cast< SystemType* >( _systems[_indices[SystemType::id()]] );
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
		std::vector< BaseType* > _systems;
		std::unordered_map< SystemBase::ID, size_t > _indices;
	};
}
