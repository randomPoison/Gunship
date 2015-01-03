#pragma once

#include "Memory/Allocator.h"

namespace Gunship
{
	namespace Memory
	{
		class StackAllocator : public Allocator
		{
		public:
			StackAllocator();

			void Init( void* buffer, size_t bytes ) override;
			void TearDown() override;

			void* Allocate( size_t size ) override;
			void Free( void* mem ) override;

			size_t Allocated() override;
			size_t Reserved() override;

		private:
			size_t _bufferSize;
			void* _stackBase;
			void* _stackTop;
			bool _initialized;
		};
	}
}
