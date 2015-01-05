#include <SDL_assert.h>

#include "Containers/ArrayBase.h"
#include "Memory/Allocator.h"

namespace Gunship
{
	ArrayBase::ArrayBase( Memory::Allocator* allocator,
	                      Memory::size_t elementSize,
	                      Memory::size_t initialCapacity )
		: _allocator( allocator ),
		  _buffer( allocator->Allocate( elementSize * initialCapacity ) ),
		  _elementSize( elementSize ),
		  _bufferSize( elementSize * initialCapacity ),
		  _bufferUsed( 0 )
	{
	}

	void ArrayBase::Grow()
	{
		// no >:(
		SDL_assert_always( false );
	}

	void* ArrayBase::AddElement()
	{
		// grow the array if not enough room for new element
		if ( count() == capacity() )
		{
			Grow();
		}

		// calculate pointer to new element and increase count
		void* element = static_cast< Memory::byte* >( _buffer ) + _bufferUsed;
		_bufferUsed += _elementSize;
		return element;
	}

	Memory::size_t ArrayBase::count() const
	{
		return _bufferUsed / _elementSize;
	}

	Memory::size_t ArrayBase::capacity() const
	{
		return _bufferSize / _elementSize;
	}

	void* ArrayBase::begin()
	{
		return _buffer;
	}

	void* ArrayBase::end()
	{
		return static_cast< Memory::byte* >( _buffer ) + _bufferUsed;
	}
}
