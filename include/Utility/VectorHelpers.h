#pragma once

#include <vector>
#include <algorithm>

namespace Gunship
{
	class VectorHelpers
	{
	public:
		template < typename T >
		static void EraseIfPresent( std::vector< T >& items, T element )
		{
			auto item = std::find( items.begin(), items.end(), element );
			if ( item != items.end() )
			{
				items.erase( item );
			}
		}

		template < typename T >
		static bool Contains( const std::vector< T >& items, T element )
		{
			auto item = std::find( items.begin(), items.end(), element );
			return item != items.end();
		}
	};
}
