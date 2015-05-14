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

	/// @brief Pushes the provided element onto the back of the list.
	///
	/// @remarks
	///     This method copy constructs a new element, so if Element
	///     does not support copy construction then you must use Emplace().
	///
	/// @todo
	///     Perhaps don't use copy assignment for this one. Can we do placement new for copy construction?
	Element& Push( const Element& element )
	{
		if ( _count == _capacity )
		{
			Reallocate();
		}

		size_t index = _count;
		_elements[index] = element;
		//new ( _elements + index ) Element;
		_count += 1;

		return _elements[index];
	}

	/// @brief Directly constructs a new element within the array.
	///
	/// @remarks
	///     This method is needed for types that cannot be copy constructed/assigned
	///     and therefore cannot be used with Push().
	///
	/// @todo
	///     Support forwarding constructor arguments like vector::emplace_back().
	Element& Emplace()
	{
		if ( _count == _capacity )
		{
			Reallocate();
		}

		size_t index = _count;
		new ( _elements + index ) Element;
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

	void FillToCount( size_t count )
	{
		// TODO: Maybe do a single allocation do ensure capacity is large enough
		// to handle the new items without doing multiple reallocations.

		while ( _count < count )
		{
			Emplace();
		}
	}

	/// @brief Check if the array contains the specified element.
	///
	/// @details
	///     This method can optionally retrieve the index of the found element. It will
	///     store the index in the index parameter if it is not null.
	size_t Contains( const Element& element, size_t* const outIndex = nullptr )
	{
		size_t index = 0;
		for ( Element* ownedElement = begin(); ownedElement != end(); ++index, ++ownedElement )
		{
			if ( *ownedElement == element )
			{
				if ( outIndex )
				{
					*outIndex = index;
				}

				return true;
			}
		}

		return false;
	}

	/// @brief Remove an element from anywhere in the array, replacing it with the last element.
	///
	/// @remarks
	///     This method does not preserve ordering but does perform removal in O(1) time.
	void SwapRemove( size_t index )
	{
		SDL_assert_paranoid( index < _count );

		_elements[index] = back();
		Pop();
	}

	Element& operator[]( size_t index )
	{
		SDL_assert_paranoid( index < _count );

		return _elements[index];
	}

	const Element& operator[]( size_t index ) const
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

	Element& front()
	{
		return _elements[0];
	}

	Element& back()
	{
		return _elements[_count - 1];
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
