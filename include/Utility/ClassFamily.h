#pragma once

namespace Gunship
{
	class ClassFamilyBase
	{
	public:
		typedef Uint32 Family;

	protected:
		static Family familyCounter;
	};

	template< typename Class >
	class ClassFamily : public ClassFamilyBase
	{
	public:

	private:
		static SystemBase::Family family()
		{
			static SystemBase::Family family = SystemBase::familyCounter++;
			return family;
		}
	};
}
