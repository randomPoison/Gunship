#pragma once

#include <utility>

#include "Utility/NonCopyable.h"

namespace Gunship
{
	template< typename Class >
	class Singleton : public NonCopyable
	{
	public:
		Class& instance()
		{
			return _instance;
		}

		template< typename ... Args >
		static void Initialize( Args&& ... args )
		{
			_instance = new Class( std::forward< Args >( args ) ... );
		}

		static void TearDown()
		{
			delete _instance;
		}

	protected:
		static Class* _instance;

		Singleton() { }
	};

	template< typename Class >
	Class* Singleton< Class >::_instance = nullptr;
}
