#pragma once

#include "Memory/MemoryTypes.h"

namespace Gunship
{
	class ArrayBase
	{
	public:
		ArrayBase( Memory::Allocator* allocator, Memory::size_t elementSize, Memory::size_t initialCapacity );

		void Grow();
		void Shrink();

		void* AddElement();

		Memory::size_t count() const;
		Memory::size_t capacity() const;

		void* begin();
		void* end();

	private:
		Memory::Allocator* _allocator;     ///< The allocator being used by this container.
		void* _buffer;                     ///< The block of memory currently being used by this container.

		const Memory::size_t _elementSize; ///< The size (in bytes) of the elements held by this array.
		Memory::size_t _bufferSize;        ///< The size (in bytes) of the memory buffer.
		Memory::size_t _bufferUsed;        ///< The size (in bytes) that has been used.
	};
}
