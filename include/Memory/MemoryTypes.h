#pragma once

#include <cstdint>

namespace Gunship
{
	namespace Memory
	{
		/*
		 * @brief Simple single-byte type for doing pointer math.
		 */
		typedef std::uint8_t byte;

		/**
		 * @brief An unsigned integral type large enough to represent any amount of allocated memory.
		 */
		typedef std::uint64_t size_t;

		/**
		 * @brief Sentinel value for signaling that an allocator is uninitialized.
		 */
		const size_t MEMORY_BUFFER_UNINITIALIZED = UINT64_MAX;

		class Allocator; // forward declaration
	}
}
