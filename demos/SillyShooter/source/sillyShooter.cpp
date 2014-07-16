#include <iostream>

#include <gunship.h>

#include "sillyShooter.h"

int main( int argc, char** argv )
{
	Gunship engine;

	if ( !engine.InitSystems() )
	{
		std::cout << "Could not initialize rendering systems!" << std::endl;
		return 1;
	}

	engine.Start();

	engine.ShutDown();

	return 0;
}