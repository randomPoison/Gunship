#include "Entity/System.h"

namespace Gunship
{

SystemBase::ID Gunship::SystemBase::idCounter = 0;

SystemBase::SystemBase()
	: active( true )
{
}

SystemBase::~SystemBase()
{
}

}
