#include <SDL_assert.h>

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

inline SDL_assert_state TestCaseAssertionHandler( const SDL_assert_data* data,
                                           void* userdata )
{
	*static_cast< bool* >( userdata ) = true;
	return SDL_ASSERTION_IGNORE;
}
