#define CATCH_CONFIG_MAIN
#include "Catch/catch.hpp"

#include <SDL_assert.h>
#include "Memory/StackAllocator.h"

#define CONFIGURE_ASSERTS() \
bool assertHit = false;\
SDL_SetAssertionHandler( TestCaseAssertionHandler, &assertHit )

#define REQUIRE_ASSERT( expression ) \
expression;\
REQUIRE( ( assertHit && #expression ) );\
assertHit = false

#define REQUIRE_NOASSERT( expression ) \
expression;\
REQUIRE( ( !assertHit && #expression ) );\
assertHit = false

SDL_assert_state TestCaseAssertionHandler( const SDL_assert_data* data,
                                           void* userdata )
{
	*static_cast< bool* >( userdata ) = true;
	return SDL_ASSERTION_IGNORE;
}

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

	// tear down allocator
	REQUIRE_NOASSERT( allocator.TearDown() );
}
