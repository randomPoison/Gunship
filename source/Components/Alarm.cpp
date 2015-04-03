#include <algorithm>

#include "Components/Alarm.h"

namespace Gunship
{
	namespace Components
	{
		AlarmManager::AlarmID AlarmManager::Assign( Entity::ID entityID, float duration, AlarmCallback callback )
		{
			AlarmID alarmID = _idCounter++;

			// Insert the new alarm into the timeline.
			auto iterator = _timeline.begin();
			for ( ; iterator != _timeline.end(); ++iterator )
			{
				if ( duration > iterator->remainingTime )
				{
					duration -= iterator->remainingTime;
				}
				else
				{
					iterator->remainingTime -= duration;
					break;
				}
			}

			// Insert the new alarm into the timeline.
			_timeline.insert( iterator, { alarmID, duration } );

			// Add the alarm data to the data map.
			_alarmData[alarmID] = { entityID, callback };

			return alarmID;
		}

		/// @todo: Actually destroy all marked alarms.
		void AlarmManager::DestroyAllMarked()
		{
		}

		void AlarmManager::DestroyImmediate( AlarmID alarmID )
		{
			// Things that need to be done:
			//
			// - Remove the alarm from the timeline and correctly update other alarms.
			// - Remove the alarm data from the data map.
			// - Call the callback.

			// TODO: Properly update the timeline after removing the data.
			auto iterator = std::find_if(
				_timeline.begin(),
				_timeline.end(),
				[=]( Alarm& alarm )
				{
					return false;
				} );
		}

		void AlarmManager::RemoveAlarms( vector< Alarm >::iterator endIterator )
		{
			_timeline.erase( _timeline.begin(), endIterator );
		}
	}
}
