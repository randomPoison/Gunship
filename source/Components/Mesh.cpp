#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include <SDL_assert.h>

#include "Scene.h"
#include "Components/Mesh.h"
#include "Components/Transform.h"

namespace Gunship
{
	namespace Components
	{
		// TODO: Actually destroy all the meshes on scene tear-down.
		//Mesh::~Mesh()
		//{
		//	sceneManager->destroyEntity( mesh );
		//}

		MeshManager::MeshManager( Scene& scene )
			: _scene( scene )
		{
		}

		Mesh& MeshManager::Assign( Entity::ID entityID, const char* meshName )
		{
			// Retrieve or create a mesh to use.
			Mesh mesh;
			if ( _pooledMeshes.count( meshName ) )
			{
				// Use pooled mesh and remove from pool.
				auto iterator = _pooledMeshes.find( meshName );

				mesh = iterator->second;
				mesh.entityID = entityID;

				_pooledMeshes.erase( iterator );
			}
			else
			{
				// Create new mesh.
				Ogre::Entity* meshEntity = _scene.sceneManager().createEntity( meshName );
				mesh.entityID = entityID;
				mesh.mesh = meshEntity;
				mesh.meshName = Ogre::String( meshName );
			}

			// Enable the component by attaching it's Ogre::Entity
			// to the node held by its transform.
			Transform& transform =
				_scene.componentManager< TransformManager >().Get( entityID );
			transform.node->attachObject( mesh.mesh );

			// Add it to the list of live meshes and add its index
			// to the index map.
			_meshes.push_back( mesh );
			_indices[entityID] = _meshes.size() - 1;

			return _meshes.back();
		}

		void MeshManager::Destroy( Entity::ID entityID )
		{
			SDL_assert_paranoid( _indices.count( entityID ) );
			SDL_assert_paranoid( !VectorHelpers::Contains( _markedForDestruction, entityID ) );

			_markedForDestruction.push_back( entityID );
		}

		const std::vector< Mesh > MeshManager::components() const
		{
			return _meshes;
		}

		void MeshManager::DestroyAll( Entity::ID entityID )
		{
			if ( _indices.count( entityID ) )
			{
				Destroy( entityID );
			}
		}

		void MeshManager::DestroyAllMarked()
		{
			for ( Entity::ID entityID : _markedForDestruction )
			{
				// We have to check first if the component exists.
				// We check when marking the component for destruction
				// that the component exists, but we don't check if its
				// already been marked, so if it doesn't exist here we
				// can assume that it was marked twice and has already
				// beend destroyed.
				if ( _indices.count( entityID ) )
				{
					DestroyImmediate( entityID );
				}
			}

			_markedForDestruction.clear();
		}

		void MeshManager::DestroyImmediate( Entity::ID entityID )
		{
			// Retrieve the index of the component to be destroyed, then
			// remove the component to be destroyed from the index map.
			size_t index = _indices[entityID];
			_indices.erase( entityID );
			Mesh& mesh = _meshes[index];

			// Disable the mesh by detaching it from it's scene node.
			SDL_assert_paranoid( mesh.mesh->getParentSceneNode() );
			mesh.mesh->detachFromParent();

			// Add the mesh back to the pool.
			_pooledMeshes.insert( { mesh.meshName, mesh } );

			// Swap the mesh if it's not already at the back of the array.
			if ( index != _meshes.size() - 1 )
			{
				std::swap( _meshes[index], _meshes.back() );
				_indices[_meshes[index].entityID] = index;
			}

			// Destroy the old component by popping it off the back.
			_meshes.pop_back();
		}
	}
}
