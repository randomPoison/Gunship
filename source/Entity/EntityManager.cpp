#include <algorithm>

#include <SDL_assert.h>

#include "Entity/EntityManager.h"
#include "Scene.h"

namespace Gunship
{
	Entity::ID EntityManager::_idCounter = 0;

	EntityManager::EntityManager( Scene& scene )
		: _scene( scene )
	{
	}

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

		_liveEntities.insert( entityID );
		return { entityID };
	}

	void EntityManager::Destroy( Entity::ID entityID )
	{
		SDL_assert_paranoid( _liveEntities.count( entityID ) );

		// Free the ID.
		_liveEntities.erase( entityID );
		_freeIDs.push_back( entityID );

		// Destroy all components associated with the entity.
		for ( auto pair : _scene._componentManagers )
		{
			pair.second->DestroyAll( entityID );
		}
	}
}
