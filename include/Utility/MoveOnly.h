#pragma once

namespace Gunship
{
	class MoveOnly
	{
	public:
		MoveOnly() = default;
		~MoveOnly() = default;

		MoveOnly( MoveOnly&& ) = default;
		MoveOnly& operator=( MoveOnly&& ) = default;

		MoveOnly( const MoveOnly& ) = delete;
		MoveOnly& operator=( const MoveOnly& ) = delete;
	};
}
