#include "Catch/catch.hpp"

#include "TestHelpers.h"
#include "Containers/Array.h"
#include "Memory/StackAllocator.h"

TEST_CASE( "Array behaves as a dynamicly sized random access container", "[containers][array]" )
{
	// create default allocator
	Gunship::Memory::Allocator* testAllocator = new Gunship::Memory::StackAllocator;
	testAllocator->Init( malloc( 1024 * 1024 * 2 ), 1024 * 1024 * 2 );

	Gunship::Array< int > array( testAllocator, 10 );

	REQUIRE( array.capacity() == 10 );
	REQUIRE( array.count() == 0 );

	SECTION( "Adding an element increases the size" )
	{
		array.PushBack( 10 );

		REQUIRE( array.count() == 1 );
		REQUIRE( array.capacity() == 10 );
	}

	SECTION( "Array automatically increases its capacity when necessary" )
	{
		for ( int count = 0; count < 11; count++ )
		{
			array.PushBack( count );
		}

		REQUIRE( array.capacity() > 10 );
	}
}
