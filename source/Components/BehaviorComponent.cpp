#include "Gunship.h"
#include "Components/BehaviorComponent.h"

BehaviorComponent::BehaviorComponent( GameObject& owner, BehaviorFunction behavior ) :
	Component( owner ),
	behavior( behavior )
{
}
