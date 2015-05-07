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

Mesh& MeshManager::Assign( Entity entity, const char* meshName )
{
	Ogre::String nameString( meshName );

	// ensure that there is a vector for the current ID
	FastArray< Mesh >& meshPool =
		_pooledMeshes.emplace( nameString, 0 ).first->second;

	// Retrieve or create a mesh to use.
	Mesh mesh;
	if ( !meshPool.empty() )
	{
		mesh = meshPool.Peek();
		mesh.entity = entity;

		meshPool.Pop();
	}
	else
	{
		// Create new mesh.
		Ogre::Entity* meshEntity = _scene.sceneManager().createEntity( nameString );
		mesh.entity = entity;
		mesh.mesh = meshEntity;
		mesh.meshPool = &meshPool;
	}

	// Enable the component by attaching it's Ogre::Entity
	// to the node held by its transform.
	Transform& transform =
		_scene.componentManager< TransformManager >().Get( entity );
	transform.node->attachObject( mesh.mesh );

	// Add it to the list of live meshes and add its index
	// to the index map.
	_meshes.Push( mesh );
	_indices.Put( entity, _meshes.count() - 1 );

	return _meshes.Peek();
}

Mesh& MeshManager::Get( Entity entity )
{
	size_t index = _indices.Get( entity );
	return _meshes[index];
}

void MeshManager::Destroy( Entity entity )
{
	_markedForDestruction.Push( entity );
}

const FastArray< Mesh > MeshManager::components() const
{
	return _meshes;
}

void MeshManager::DestroyAll( Entity entity )
{
	Destroy( entity );
}

void MeshManager::DestroyAllMarked()
{
	for ( Entity entity : _markedForDestruction )
	{
		// We have to check first if the component exists.
		// We check when marking the component for destruction
		// that the component exists, but we don't check if its
		// already been marked, so if it doesn't exist here we
		// can assume that it was marked twice and has already
		// beend destroyed.
		if ( _indices.Contains( entity ) )
		{
			DestroyImmediate( entity );
		}
	}

	_markedForDestruction.Clear();
}

void MeshManager::DestroyImmediate( Entity entity )
{
	// Retrieve the index of the component to be destroyed, then
	// remove the component to be destroyed from the index map.
	size_t index = _indices.Get( entity );
	_indices.Remove( entity );

	// Disable the mesh by detaching it from it's scene node.
	Mesh& mesh = _meshes[index];
	mesh.mesh->detachFromParent();

	// Add the mesh back to the pool.
	mesh.meshPool->Push( mesh );

	// Swap the mesh if it's not already at the back of the array.
	if ( index != _meshes.count() - 1 )
	{
		std::swap( _meshes[index], _meshes.Peek() );
		_indices.Get(_meshes[index].entity) = index;
	}

	// Destroy the old component by popping it off the back.
	_meshes.Pop();
}

}
}
