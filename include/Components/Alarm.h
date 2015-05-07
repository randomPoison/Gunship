#pragma once

#include <vector>        ///< @todo Remove dependence on STL containers.
#include <unordered_map> ///< @todo Remove dependence on STL containers.
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

			/// @brief Registers the alarm with the alarm manager.
			///
			/// @note
			///     The alarm is not added immediately to the timeline, rather
			///     it is queued up as pending and all pending alarms are added
			///     to the timeline after the component destruction sweep. This
			///     is done to handle the case where an alarm callback registers
			///     new alarms with the manager.
			AlarmID Assign( Entity entity, float duration, AlarmCallback callback );

			/// @brief Marks a given alarm to be cancelled.
			///
			/// @note
			///     This does not immediately cancel the alarm, it only
			///     marks the alarm to be removed from the timeline during
			///     the component destruction sweep. However, since the
			///     destruction sweep takes place before the next alarm
			///     tick, the alarm is guaranteed not to go off after it's
			///     been cancelled.
			void Cancel( AlarmID alarmID );

			void DestroyAll( Entity entity ) override;

		private:
			struct Alarm
			{
				AlarmID id;
				float remainingTime;
			};

			struct AlarmData
			{
				Entity entity;
				AlarmCallback callback;
			};

			struct PendingAlarm
			{
				AlarmID alarmID;
				float duration;
			};

			vector< Alarm > _timeline;
			unordered_map< AlarmID, AlarmData > _alarmData;
			vector< AlarmID > _cancelled;
			vector< PendingAlarm > _pendingForAdd;

			AlarmID _idCounter;

			void DestroyAllMarked() override;
			void DestroyImmediate( AlarmID alarmID );

			/// @brief Removes the first alarm through the specified alarm.
			///
			/// @details
			///     If \a endIterator points to the first alarm then no
			///     alarms are removed.
			void RemoveAlarms( vector< Alarm >::iterator endIterator );

			friend struct Systems::AlarmSystem;
		};
	}
}
