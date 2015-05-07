#pragma once

#include <cstdlib>
#include <cstring>

#include <SDL_assert.h>

namespace Gunship {
namespace Containers {

template < typename Element >
class FastArray
{
public:
	FastArray( size_t capacity = 8 )
		: _elements( Allocate( capacity ) ),
		  _capacity( capacity ),
		  _count( 0 )
	{
	}

	FastArray( FastArray&& other )
		: _elements( other._elements ),
		  _capacity( other._capacity ),
		  _count( other._count )
	{
		other._elements = nullptr;
	}

	~FastArray()
	{
		free( _elements );
	}

	Element& Push( Element& element )
	{
		if ( _count == _capacity )
		{
			Reallocate();
		}

		size_t index = _count;
		_elements[index] = element;
		_count += 1;

		return _elements[index];
	}

	Element& Peek()
	{
		SDL_assert_paranoid( _count > 0 );

		return _elements[_count - 1];
	}

	void Pop()
	{
		SDL_assert_paranoid( _count > 0 );

		// This array is for lightweight data, so we don't bother calling
		// the destructor on the removed element.
		_count -= 1;
	}

	void Clear()
	{
		_count = 0;
	}

	Element& operator[]( size_t index )
	{
		SDL_assert_paranoid( index < _count );

		return _elements[index];
	}

	bool empty() const
	{
		return _count == 0;
	}

	size_t count() const
	{
		return _count;
	}

	Element* begin()
	{
		return _elements;
	}

	Element* end()
	{
		return _elements + _count;
	}

	const Element* begin() const
	{
		return _elements;
	}

	const Element* end() const
	{
		return _elements + _count;
	}

private:
	Element* _elements;
	size_t _capacity;
	size_t _count;

	static Element* Allocate( size_t count )
	{
		void* rawBytes = calloc( count, sizeof( Element ) );
		return static_cast< Element* >( rawBytes );
	}

	void Reallocate()
	{
		Element* oldElements = _elements;

		// Increase the capacity and allocate a new buffer.
		_capacity *= 2;
		_elements = Allocate( _capacity );

		// Copy the old elements to the new buffers.
		memcpy( _elements, oldElements, _count * sizeof( Element ) );

		// Free the old buffer.
		free( oldElements );
	}
};

}
}
