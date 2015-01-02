#include <OgreLight.h>
#include <OgreSceneManager.h>

#include "Scene.h"
#include "Components/Light.h"
#include "Components/Transform.h"

namespace Gunship
{
	namespace Components
	{
		Light::Light( const Scene& scene, const Transform* transform )
			: light( nullptr )
		{
			light = scene.sceneManager().createLight();
			transform->node->attachObject( light );
		}
	}
}
