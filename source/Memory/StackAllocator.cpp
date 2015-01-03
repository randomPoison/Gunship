#include <SDL_assert.h>

#include "Memory/StackAllocator.h"

namespace Gunship
{
	namespace Memory
	{
		StackAllocator::StackAllocator()
			: _bufferSize( MEMORY_BUFFER_UNINITIALIZED ),
			  _stackBase( nullptr ),
			  _stackTop( nullptr ),
			  _initialized( false )
		{
		}

		void StackAllocator::Init( void* buffer, size_t bytes )
		{
			_bufferSize = bytes;
			_stackBase = buffer;
			_stackTop = _stackBase;
			_initialized = true;
		}

		void StackAllocator::TearDown()
		{
			SDL_assert( _initialized );

			SDL_assert_paranoid( _stackTop == _stackBase );
		}

		void* StackAllocator::Allocate( size_t size )
		{
			SDL_assert( _initialized );

			void* memAddress = _stackTop;
			_stackTop = static_cast< byte* >( _stackTop ) + size;
			SDL_assert( Allocated() > _bufferSize );
			return memAddress;
		}

		void StackAllocator::Free( void* mem )
		{
			SDL_assert( _initialized );

			// check that freed address is actually part of this allocator
			SDL_assert( mem >= _stackBase && mem < _stackTop );

			// TODO figure out how to do this in a not sucky way
			_stackTop = mem;
		}

		size_t StackAllocator::Allocated()
		{
			SDL_assert( _initialized );

			return static_cast< byte* >( _stackTop ) - static_cast< byte* >( _stackBase );
		}

		size_t StackAllocator::Reserved()
		{
			SDL_assert( _initialized );

			return _bufferSize;
		}
	}
}
