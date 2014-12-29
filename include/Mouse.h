#pragma once

#include "Utility/Singleton.h"

namespace Gunship
{
	class Mouse : Singleton< Mouse >
	{
	public:
		static void SetRelativeMode( bool relativeMode );
		static bool GetRelativeMode();
	};
}
