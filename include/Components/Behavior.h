#pragma once

class Behavior final : public ComponentLocator
{
public:
	Behavior( Scene& scene, component_id id, size_t index = 0 );

	void Destroy() override;
};
