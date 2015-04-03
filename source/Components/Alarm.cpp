#include <algorithm>

#include <SDL_assert.h>

#include "Components/Alarm.h"
#include "Utility/VectorHelpers.h"

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

		void AlarmManager::Cancel( AlarmID alarmID )
		{
			SDL_assert_paranoid( _alarmData.count( alarmID ) );

			_cancelled.push_back( alarmID );
		}

		void AlarmManager::DestroyAllMarked()
		{
			for ( AlarmID alarmID : _cancelled )
			{
				DestroyImmediate( alarmID );
			}

			_cancelled.clear();
		}

		void AlarmManager::DestroyImmediate( AlarmID alarmID )
		{
			// Remove alarm data from the data map.
			_alarmData.erase( alarmID );

			// Remove the alarm from the timeline, adding its
			// time to the next alarm to keep things in sync.
			auto alarm = std::find_if(
				_timeline.begin(), _timeline.end(),
				[=]( Alarm& alarm ) { return alarm.id == alarmID; } );

			SDL_assert_paranoid( alarm != _timeline.end() );

			// If alarm isn't last in timeline, add it's time to
			// the alarm that follows it.
			auto nextAlarm = alarm + 1;
			if ( nextAlarm != _timeline.end() )
			{
				nextAlarm->remainingTime += alarm->remainingTime;
			}

			// Remove the alarm from the timeline.
			_timeline.erase( alarm );
		}

		void AlarmManager::RemoveAlarms( vector< Alarm >::iterator endIterator )
		{
			_timeline.erase( _timeline.begin(), endIterator );
		}
	}
}
