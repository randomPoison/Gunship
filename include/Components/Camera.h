#pragma once

class Camera final : ComponentLocator
{
public:
	Camera( Scene* scene = nullptr, component_id id = 0, size_t index = 0 );

	void Destroy() override;
};
