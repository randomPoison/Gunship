#include "Gunship.h"
#include "Components/Camera.h"

Camera::Camera( Scene* scene, component_id id, size_t index ) : ComponentLocator( scene, id, index )
{
}

void Camera::Destroy()
{
}
