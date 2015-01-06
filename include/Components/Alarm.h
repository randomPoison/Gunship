#pragma once

#include <functional>

#include "Entity/ComponentManager.h"
#include "Components/SimpleStructComponent.h"

namespace Gunship
{
	class Scene;

	namespace Components
	{
		struct Alarm : public SimpleStructComponent
		{
			typedef std::function< void( Scene&, Gunship::Entity ) > AlarmCallback;

			float remainingTime;
			AlarmCallback callback;

			Alarm( float startAlarm, AlarmCallback callback );
		};
	}
}
