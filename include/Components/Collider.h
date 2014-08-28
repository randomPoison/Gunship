#pragma once

class Collider : public ComponentLocator
{
public:
	Collider( Scene& scene, component_id component, size_t index = 0 );

	/**
	 * \brief Check if the collider collided this frame.
	 *
	 * \returns True if there was a collision, false otherwise.
	 */
	bool Collided();

	/**
	 * \brief Retrieve all the collisions from the last frame.
	 *
	 * \returns The other ColliderComponent objects that the callee collided with.
	 */
	std::vector< Collider > Collisions();

	void Destroy() override;
};
