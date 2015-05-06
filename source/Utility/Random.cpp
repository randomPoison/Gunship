#include <functional>
#include <time.h>

#include "Utility/Random.h"

Random Random::_instance;

Random::Random()
{
#if _DEBUG
	_generator.seed( 1 );
#else
	_generator.seed( time( nullptr ) );
#endif
}

int Random::Range( int min, int max )
{
	return std::uniform_int_distribution<int>( min, max )( _instance._generator );
}

float Random::Range( float min, float max )
{
	return ( std::uniform_real_distribution<float>( min, max ) )( _instance._generator );
}

bool Random::Probability( float chance )
{
	static std::uniform_real_distribution<float> floatDistribution( 0.0f, 1.0f );
	return floatDistribution( _instance._generator ) < chance;
}
