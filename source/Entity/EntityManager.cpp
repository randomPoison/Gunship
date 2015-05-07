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
		Entity entity;

		if ( !_freeIDs.empty() )
		{
			entity = _freeIDs.back();
			_freeIDs.pop_back();
		}
		else
		{
			entity.id = _idCounter++;
		}

		_liveEntities.Put( entity );
		return { entity };
	}

	void EntityManager::Destroy( Entity entity )
	{
		SDL_assert_paranoid( _liveEntities.Contains( entity ) );

		// Free the ID.
		_liveEntities.Remove( entity );
		_freeIDs.push_back( entity );

		// Destroy all components associated with the entity.
		for ( auto pair : _scene._componentManagers )
		{
			pair->DestroyAll( entity );
		}
	}
}
