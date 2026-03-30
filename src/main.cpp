#include <raylib.h>
#include "simulation.h"
#include "display.h"

int main() 
{
	InitDisplay();	
	Start();
	
	while(!WindowShouldClose()) 
	{
		Update(GetFrameTime());
		Draw();
	}
	
	return 0;
}