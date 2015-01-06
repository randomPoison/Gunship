#include <algorithm>

#include <SDL_assert.h>

#include "Entity/EntityManager.h"

namespace Gunship
{
	Entity::ID EntityManager::_idCounter = 0;

	Entity EntityManager::Create()
	{
		Entity::ID entityID;

		if ( !_freeIDs.empty() )
		{
			entityID = _freeIDs.front();
			_freeIDs.pop_front();
		}
		else
		{
			entityID  = _idCounter++;
		}

		_liveEntities.push_back( entityID );
		return { entityID };
	}

	void EntityManager::Destroy( Entity entity )
	{
		Destroy( entity.id );
	}

	void EntityManager::Destroy( Entity::ID entityID )
	{
		auto iterator = std::find( _liveEntities.begin(), _liveEntities.end(), entityID );
		SDL_assert_paranoid( iterator != _liveEntities.end() );
		_liveEntities.erase( iterator );
		_freeIDs.push_back( entityID );
	}
}
