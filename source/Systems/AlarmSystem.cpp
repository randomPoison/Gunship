#include "Systems/AlarmSystem.h"
#include "Components/Alarm.h"
#include "Scene.h"

using Gunship::Components::AlarmManager;

namespace Gunship
{
	namespace Systems
	{
		void AlarmSystem::Update( Scene& scene, float delta )
		{
			AlarmManager& alarmManager =
				scene.componentManager< AlarmManager >();
			auto iterator = alarmManager._timeline.begin();
			for ( ; delta > 0.0f && iterator != alarmManager._timeline.end(); ++iterator )
			{
				if ( delta > iterator->remainingTime )
				{
					// Update the remaining time delta.
					delta -= iterator->remainingTime;

					// Call the callback.
					auto& alarmData = alarmManager._alarmData[iterator->id];
					alarmData.callback( scene, { alarmData.entity } );
				}
				else
				{
					iterator->remainingTime -= delta;
					break;
				}
			}

			// Remove all alarms that have finished.
			// If iterator points to the first alarm, nothing is removed.
			alarmManager.RemoveAlarms( iterator );
		}
	}
}
