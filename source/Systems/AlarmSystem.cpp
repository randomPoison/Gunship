#include <iostream>

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

			auto& iterator = alarmManager._timeline.begin();
			for ( ; delta > 0.0f && iterator != alarmManager._timeline.end(); ++iterator )
			{
				std::cout << "remaining time: " << iterator->remainingTime
					<< ", delta: " << delta << std::endl;

				if ( delta > iterator->remainingTime )
				{
					// Call the callback.
					auto& alarmData = alarmManager._alarmData[iterator->id];
					alarmData.callback( scene, { alarmData.entityID } );
				}
				else
				{
					iterator->remainingTime -= delta;
					break;
				}

				delta -= iterator->remainingTime;
			}

			if ( iterator != alarmManager._timeline.begin() )
			{
				alarmManager.RemoveAlarms( iterator );
			}
		}
	}
}
