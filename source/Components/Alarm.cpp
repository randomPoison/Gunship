#include "Components/Alarm.h"

namespace Gunship
{
	namespace Components
	{
		Alarm::Alarm( float startTime, AlarmCallback callback )
			: remainingTime( startTime ),
			  callback( callback )
		{
		}
	}
}
