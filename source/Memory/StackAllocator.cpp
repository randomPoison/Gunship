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
			SDL_assert_paranoid( !_initialized );

			_bufferSize = bytes;
			_stackBase = buffer;
			_stackTop = _stackBase;
			_initialized = true;
		}

		void StackAllocator::TearDown()
		{
			SDL_assert_paranoid( _initialized );
			SDL_assert_release( _stackTop == _stackBase );

			_initialized = false;
		}

		void* StackAllocator::Allocate( size_t size )
		{
			SDL_assert_paranoid( _initialized );

			void* memAddress = _stackTop;
			_stackTop = static_cast< byte* >( _stackTop ) + size;
			SDL_assert_paranoid( allocated() <= _bufferSize );
			return memAddress;
		}

		void StackAllocator::Free( void* mem )
		{
			SDL_assert_paranoid( _initialized );
			SDL_assert_paranoid( mem != nullptr );
			SDL_assert_paranoid( mem >= _stackBase && mem < _stackTop ); // check that freed address is actually part of this allocator

			_stackTop = mem;
		}

		size_t StackAllocator::allocated()
		{
			SDL_assert_paranoid( _initialized );

			return static_cast< byte* >( _stackTop ) - static_cast< byte* >( _stackBase );
		}

		size_t StackAllocator::reserved()
		{
			SDL_assert_paranoid( _initialized );

			return _bufferSize;
		}
	}

	Memory::Allocator* gDefaultAllocator;
}
