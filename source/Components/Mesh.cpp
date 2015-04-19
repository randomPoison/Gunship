#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include <SDL_assert.h>

#include "Scene.h"
#include "Components/Mesh.h"
#include "Components/Transform.h"

using Gunship::Containers::FastArray;

namespace Gunship {
namespace Components {

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
	// ensure that there is a vector for the current ID
	FastArray< Mesh >& meshPool =
		_pooledMeshes.insert( { meshName, FastArray< Mesh >() } ).first->second;

	// Retrieve or create a mesh to use.
	Mesh mesh;
	if ( !meshPool.empty() )
	{
		mesh = meshPool.Peek();
		mesh.entityID = entityID;

		meshPool.Pop();
	}
	else
	{
		// Create new mesh.
		Ogre::Entity* meshEntity = _scene.sceneManager().createEntity( meshName );
		mesh.entityID = entityID;
		mesh.mesh = meshEntity;
		mesh.meshPool = &meshPool;
	}

	// Enable the component by attaching it's Ogre::Entity
	// to the node held by its transform.
	Transform& transform =
		_scene.componentManager< TransformManager >().Get( entityID );
	transform.node->attachObject( mesh.mesh );

	// Add it to the list of live meshes and add its index
	// to the index map.
	_meshes.Push( mesh );
	_indices.Put( entityID, _meshes.count() - 1 );

	return _meshes.Peek();
}

void MeshManager::Destroy( Entity::ID entityID )
{
	_markedForDestruction.Push( entityID );
}

const FastArray< Mesh > MeshManager::components() const
{
	return _meshes;
}

void MeshManager::DestroyAll( Entity::ID entityID )
{
	Destroy( entityID );
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
		if ( _indices.Contains( entityID ) )
		{
			DestroyImmediate( entityID );
		}
	}

	_markedForDestruction.Clear();
}

void MeshManager::DestroyImmediate( Entity::ID entityID )
{
	// Retrieve the index of the component to be destroyed, then
	// remove the component to be destroyed from the index map.
	size_t index = _indices.Get( entityID );
	_indices.Remove( entityID );

	// Disable the mesh by detaching it from it's scene node.
	Mesh& mesh = _meshes[index];
	mesh.mesh->detachFromParent();

	// Add the mesh back to the pool.
	mesh.meshPool->Push( mesh );

	// Swap the mesh if it's not already at the back of the array.
	if ( index != _meshes.count() - 1 )
	{
		std::swap( _meshes[index], _meshes.Peek() );
		_indices.Get(_meshes[index].entityID) = index;
	}

	// Destroy the old component by popping it off the back.
	_meshes.Pop();
}

}
}
