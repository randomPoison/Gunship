#include "Gunship.h"
#include "Components/ColliderComponent.h"

ColliderComponent::ColliderComponent( GameObject& owner, float radius ) :
	Component( owner ),
	radius( radius )
{
}

bool ColliderComponent::Collide( ColliderComponent& first, ColliderComponent& second )
{
	Ogre::Vector3 firstPos = first.owner.Position();
	Ogre::Vector3 secondPos = second.owner.Position();
	return (firstPos - secondPos).squaredLength() < ( first.radius + second.radius ) * ( first.radius + second.radius );
}
