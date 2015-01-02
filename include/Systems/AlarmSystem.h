#pragma once

#include "Entity/System.h"

namespace Gunship
{
	namespace Systems
	{
		struct AlarmSystem : public System< AlarmSystem, Gunship::DefaultSystemBase >
		{
			void Update( Scene& scene, float delta ) override;
		};
	}
}
