#pragma once

#include <vector>        /// @todo Remove dependence on STL containers.
#include <unordered_map> /// @todo Remove dependence on STL containers.
#include <functional>
#include <cstdint>

#include "Entity/Entity.h"
#include "Entity/ComponentManager.h"

/// @todo Should these be at the global level? They introduce global names for every file that includes them if they are.
using std::vector;
using std::unordered_map;

namespace Gunship
{
	class Scene;

	namespace Systems
	{
		struct AlarmSystem;
	}

	namespace Components
	{
		class AlarmManager : public ComponentManager< AlarmManager >
		{
		public:
			typedef size_t AlarmID;
			typedef std::function< void( Scene&, Entity ) > AlarmCallback;

			AlarmID Assign( Entity::ID entityID, float duration, AlarmCallback callback );
			void Destroy( AlarmID alarmID );

		private:
			struct Alarm
			{
				AlarmID id;
				float remainingTime;
			};

			struct AlarmData
			{
				Entity::ID entityID;
				AlarmCallback callback;
			};

			vector< Alarm > _timeline;
			unordered_map< AlarmID, AlarmData > _alarmData;

			AlarmID _idCounter;

			void DestroyAllMarked() override;
			void DestroyImmediate( AlarmID alarmID );

			/**
			 * @brief Removes the first alarm through the specified alarm.
			 */
			void RemoveAlarms( vector< Alarm >::iterator endIterator );

			friend struct Systems::AlarmSystem;
		};
	}
}
