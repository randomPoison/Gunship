#include "Engine.h"

int main( int argc, char* argv[] )
{
	Gunship::Engine engine;

	// initialize and run the engine
	if ( engine.InitSystems() )
	{
		engine.ResetCurrentScene();
		engine.Start();
		engine.ShutDown();
	}

	return 0;
}
