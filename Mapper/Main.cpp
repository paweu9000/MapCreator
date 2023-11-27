#include "Program.h"

int main(int argc, char* args[])
{
	Program program;
	bool success = program.Initialize();
	if (success)
	{
		program.RunLoop();
	}
	program.Shutdown();

	return 0;
}