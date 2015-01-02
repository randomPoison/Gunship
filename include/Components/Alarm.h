#pragma once

#include <functional>

#include "Entity/ComponentManager.h"

namespace Gunship
{
	class Scene;

	namespace Components
	{
		struct Alarm : public entityx::Component< Alarm >
		{
			typedef std::function< void( Scene&, entityx::Entity ) > AlarmCallback;

			float remainingTime;
			AlarmCallback callback;

			Alarm( float startAlarm, AlarmCallback callback );
		};
	}
}
