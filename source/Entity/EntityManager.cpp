#include <algorithm>

#include <SDL_assert.h>

#include "Entity/EntityManager.h"
#include "Scene.h"

namespace Gunship
{
	Entity::ID EntityManager::_idCounter = 1;

	EntityManager::EntityManager( Scene& scene )
		: _scene( scene )
	{
	}

	Entity EntityManager::Create()
	{
		Entity::ID entityID;

		if ( !_freeIDs.empty() )
		{
			entityID = _freeIDs.back();
			_freeIDs.pop_back();
		}
		else
		{
			entityID  = _idCounter++;
		}

		_liveEntities.Put( entityID );
		return { entityID };
	}

	void EntityManager::Destroy( Entity::ID entityID )
	{
		SDL_assert_paranoid( _liveEntities.Contains( entityID ) );

		// Free the ID.
		_liveEntities.Remove( entityID );
		_freeIDs.push_back( entityID );

		// Destroy all components associated with the entity.
		for ( auto pair : _scene._componentManagers )
		{
			pair->DestroyAll( entityID );
		}
	}
}
