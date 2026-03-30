#include <raylib.h>
#include "simulation.h"
#include "display.h"

int main() 
{
	InitWindow(800, 600, "Gravity");
	SetWindowMonitor(0);
	
	Start();
	
	while(!WindowShouldClose()) 
	{
		Update(GetFrameTime());
		Draw();
	}
	
	return 0;
}