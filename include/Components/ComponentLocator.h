#pragma once

class Scene;

class ComponentLocator
{
public:
	ComponentLocator( Scene* scene = nullptr, component_id id = 0, size_t index = 0 );
	
	/**
	 * \brief Marks the referred to component for destruction.
	 *
	 * \note The component is only marked for destruction, and will not
	 * be destroyed until after the completion of the current frame.
	 * That means that the object may have at most one more update
	 * before it is actually destroyed.
	 */
	virtual void Destroy() = 0;

	Scene* scene;
	component_id id;
	size_t index;
};

bool operator==( const ComponentLocator& first, const ComponentLocator& second );
