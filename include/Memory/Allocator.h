#pragma once

#include <cstdint>

#include "Utility/NonCopyable.h"

namespace Gunship
{
	namespace Memory
	{
		typedef std::uint8_t byte;

		/**
		 * @brief An unsigned integral type large enough to represent any amount of allocated memory.
		 */
		typedef std::uint64_t size_t;

		const size_t MEMORY_BUFFER_UNINITIALIZED = UINT64_MAX;

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
		 *     would imply
		 */
		class Allocator : public NonCopyable
		{
		public:
			virtual ~Allocator() = default;

			virtual void Init( void* buffer, size_t bytes ) = 0;
			virtual void TearDown() = 0;

			virtual void* Allocate( size_t size ) = 0;
			virtual void Free( void* mem ) = 0;

			virtual size_t Allocated() = 0;
			virtual size_t Reserved() = 0;
		};
	}
}
