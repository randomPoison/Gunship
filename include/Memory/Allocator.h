#pragma once

#include "Memory/MemoryTypes.h"
#include "Utility/NonCopyable.h"

namespace Gunship
{
	namespace Memory
	{
		/**
		 * @brief Basic allocator interface.
		 *
		 * @details
		 *     This defines the interface for all allocators in Gunship.
		 *     In theory, this means that allocators are interchangeable,
		 *     and all containers, etc., can use any allocator.
		 *
		 * @note
		 *     Allocators are non-copyable, because copying an allocator
		 *     would imply copying its buffer, which is rarely desirable.
		 */
		class Allocator : public NonCopyable
		{
		public:
			virtual ~Allocator() = default;

			virtual void Init( void* buffer, size_t bytes ) = 0;
			virtual void TearDown() = 0;

			virtual void* Allocate( size_t size ) = 0;
			virtual void Free( void* mem ) = 0;

			virtual void* AllocateArray( size_t elementSize, size_t count ) = 0;
			virtual void FreeArray( void* mem ) = 0;

			virtual size_t allocated() = 0;
			virtual size_t reserved() = 0;
		};
	}
}
