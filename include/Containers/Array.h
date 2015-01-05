#pragma once

#include "Containers/ArrayBase.h"

namespace Gunship
{
	template< typename Element >
	class Array : private ArrayBase
	{
	public:
		typedef Element* Iterator;
		typedef const Element* ConstIterator;

		Array( Memory::Allocator* allocator, Memory::size_t initialCapacity = 8 )
			: ArrayBase( allocator, sizeof( Element ), initialCapacity )
		{
		}

		Element& PushBack( const Element& element )
		{
			Element* newElementPtr = new( AddElement() ) Element( element );
			return *newElementPtr;
		}

		Iterator begin()
		{
			return static_cast< Iterator >( ArrayBase::begin() );
		}

		Iterator end()
		{
			return static_cast< Iterator >( ArrayBase::end() );
		}

		ConstIterator begin() const;
		ConstIterator end() const;

	private:
	};
}
