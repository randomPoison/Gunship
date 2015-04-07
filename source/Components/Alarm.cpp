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
			// Add the alarm to the pending queue.
			AlarmID alarmID = _idCounter++;
			_pendingForAdd.push_back( { alarmID, duration } );

			// Add the alarm data to the data map.
			_alarmData[alarmID] = { entityID, callback };
			return alarmID;
		}

		void AlarmManager::Cancel( AlarmID alarmID )
		{
			SDL_assert_paranoid( _alarmData.count( alarmID ) );
			SDL_assert_paranoid( !VectorHelpers::Contains( _cancelled, alarmID ) );

			_cancelled.push_back( alarmID );
		}

		void AlarmManager::DestroyAll( Entity::ID entityID )
		{
			for ( auto pair : _alarmData )
			{
				if ( pair.second.entityID == entityID &&
				     VectorHelpers::Contains( _cancelled, pair.first ) )
				{
					Cancel( pair.first );
				}
			}
		}

		void AlarmManager::DestroyAllMarked()
		{
			// Add pending alarms.
			for ( PendingAlarm& pendingAlarm : _pendingForAdd )
			{
				// Find the new alarm's place in the timeline.
				auto iterator = _timeline.begin();
				for ( ; iterator != _timeline.end(); ++iterator )
				{
					if ( pendingAlarm.duration > iterator->remainingTime )
					{
						pendingAlarm.duration -= iterator->remainingTime;
					}
					else
					{
						iterator->remainingTime -= pendingAlarm.duration;
						break;
					}
				}

				// Insert the new alarm into the timeline.
				_timeline.insert( iterator, { pendingAlarm.alarmID, pendingAlarm.duration } );
			}

			_pendingForAdd.clear();

			// Destroy marked alarms.
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
