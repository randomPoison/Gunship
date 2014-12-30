#pragma once

#include <vector>
#include <algorithm>

namespace Gunship
{
	namespace Utility
	{
		template< typename T >
		void EraseIfPresent( std::vector< T >& items, T element )
		{
			auto item = std::find( items.begin(), items.end(), element );
			if ( item != items.end() )
			{
				items.erase( item );
			}
		}
	}
}
