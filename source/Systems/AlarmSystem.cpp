#include "Systems/AlarmSystem.h"
//#include "Components/Alarm.h"
#include "Scene.h"

namespace Gunship
{
	namespace Systems
	{
		void AlarmSystem::Update( Scene& scene, float delta )
		{
/*
			for ( Gunship::Entity entity : scene.entities().entities_with_components< Components::Alarm >() )
			{
				Components::Alarm& alarm = *entity.component< Components::Alarm >().get();
				alarm.remainingTime -= delta;
				if ( alarm.remainingTime < 0.0f )
				{
					alarm.callback( scene, entity );
				}
			}
*/
		}
	}
}
