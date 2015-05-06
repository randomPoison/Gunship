#pragma once

#include <random>

class Random
{
public:

	/**
	 * @brief Generate a random integer between two bounds.
	 *
	 * @param min The minimum value that can be generated, inclusive.
	 * @param max The maximum value that can be generated, inclusive.
	 * @returns A random integer value between \a min and \a max.
	 */
	static int Range( int min, int max );

	/**
	 * @brief Generate a random float between two bounds.
	 *
	 * @param min The minimum value that can be generated, inclusive.
	 * @param max The maximum value that can be generated, exclusive.
	 * @returns A random float value between \a min and \a max.
	 */
	static float Range( float min, float max );

	/**
	 * @brief Make a roll of a given probability.
	 *
	 * @param chance The likelihood of this function returning true.
	 * @returns true \a chance% of calls, false ( 1 - \a chance )% of calls.
	 */
	static bool Probability( float chance );

private:
	Random();

	static Random _instance;

	std::default_random_engine _generator;
};
