#include <raylib.h>
#include "data.h"

void Draw() 
{
	float aspect = (float)GetScreenWidth() / (float)GetScreenHeight();
	
	BeginDrawing();
	
	ClearBackground(BLACK);
	DrawCircleLinesV(Vector2(400, 300), 300, WHITE);
	
	for (int i = 0; i < planets.size(); i++) 
	{
		Vector2 localPos = Vector2((planets[i].pos.x + aspect * astroUnit) / (aspect * 2.0f * astroUnit), (planets[i].pos.y + astroUnit) / (2.0f * astroUnit));
		Vector2 screenPos = Vector2(localPos.x * GetScreenWidth(), localPos.y * GetScreenHeight());
		
		DrawCircleV(screenPos, planets[i].radius, planets[i].color);
	}
	
	EndDrawing();
}