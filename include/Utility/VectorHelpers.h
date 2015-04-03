#pragma once

#include <vector>
#include <algorithm>
#include <functional>

namespace Gunship
{
	class VectorHelpers
	{
	public:
		template < typename T >
		static void EraseIfPresent( std::vector< T >& items, T element )
		{
			auto iterator = std::find( items.begin(), items.end(), element );
			if ( iterator != items.end() )
			{
				items.erase( iterator );
			}
		}

		template < typename T >
		static void EraseIfPresent_If( std::vector< T >& items, std::function< bool( T& ) > predicate )
		{
			auto iterator = std::find_if( items.begin(), items.end(), predicate );
			if ( iterator != items.end() )
			{
				items.erase( iterator );
			}
		}

		template < typename T >
		static bool Contains( const std::vector< T >& items, T element )
		{
			auto iterator = std::find( items.begin(), items.end(), element );
			return iterator != items.end();
		}
	};
}
