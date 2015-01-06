#include "Catch/catch.hpp"

#include "TestHelpers.h"
#include "Memory/StackAllocator.h"

TEST_CASE( "Stack allocator asserts when not initialized", "[memory][stack_allocator]" )
{
	CONFIGURE_ASSERTS();

	Gunship::Memory::size_t BUFFER_SIZE = 1024;
	void* buffer = malloc( BUFFER_SIZE );

	Gunship::Memory::StackAllocator allocator;

	REQUIRE_ASSERT( allocator.TearDown() );
	REQUIRE_ASSERT( allocator.Allocate( 0 ) );
	REQUIRE_ASSERT( allocator.Free( nullptr ) );
	REQUIRE_ASSERT( allocator.reserved() );
	REQUIRE_ASSERT( allocator.allocated() );

	REQUIRE_NOASSERT( allocator.Init( buffer, BUFFER_SIZE ) );

	void* bytes;
	REQUIRE_NOASSERT( bytes = allocator.Allocate( 4 ) );
	REQUIRE_NOASSERT( allocator.Free( bytes ) );
	REQUIRE_NOASSERT( allocator.reserved() );
	REQUIRE_NOASSERT( allocator.allocated() );

	REQUIRE_NOASSERT( allocator.TearDown() );

	REQUIRE_ASSERT( allocator.TearDown() );
	REQUIRE_ASSERT( allocator.Allocate( 0 ) );
	REQUIRE_ASSERT( allocator.Free( nullptr ) );
	REQUIRE_ASSERT( allocator.reserved() );
	REQUIRE_ASSERT( allocator.allocated() );
}

TEST_CASE( "Stack allocator allocates and frees memory", "[memory][stack_allocator]" )
{
	CONFIGURE_ASSERTS();

	// get a test buffer
	Gunship::Memory::size_t BUFFER_SIZE = 1024;
	void* buffer = malloc( BUFFER_SIZE );

	// initialize allocator
	Gunship::Memory::StackAllocator allocator;
	allocator.Init( buffer, BUFFER_SIZE );

	REQUIRE( allocator.reserved() == BUFFER_SIZE );
	REQUIRE( allocator.allocated() == 0 );

	SECTION( "Stack allocator tracks allocated memory" )
	{
		Gunship::Memory::size_t allocationSize = 16;
		void* bytes = allocator.Allocate( allocationSize );

		REQUIRE( bytes != nullptr );
		REQUIRE( allocator.allocated() == allocationSize );

		allocator.Free( bytes );
		REQUIRE( allocator.allocated() == 0 );
	}

	SECTION( "Stack allocator does not allow more than the buffer size to be allocated." )
	{
		void* bytes;
		REQUIRE_NOASSERT( bytes = allocator.Allocate( BUFFER_SIZE ) );

		REQUIRE_ASSERT( allocator.Allocate( 1 ) );

		allocator.Free( bytes ); // no requirements here since
		                         // behavior after too large allocations
		                         // is undefined.
	}

	SECTION( "Stack allocator frees all memory up to the free marker" )
	{
		void* marker;
		marker = allocator.Allocate( 4 );allocator.Allocate( 4 );
		allocator.Free( marker );
		REQUIRE( allocator.allocated() == 0 );
	}

	SECTION( "Stack allocator correctly allocates and frees arrays" )
	{
		void* mem = allocator.AllocateArray( sizeof( int ), 10 );
		REQUIRE( allocator.allocated() == sizeof( int ) * 10 );

		allocator.FreeArray( mem );
		REQUIRE( allocator.allocated() == 0 );
	}

	// tear down allocator
	REQUIRE_NOASSERT( allocator.TearDown() );
}
