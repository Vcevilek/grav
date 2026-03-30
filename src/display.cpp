#include <raylib.h>
#include "data.h"
#include "circular_buffer.h"

AstroCam camera;

void InitDisplay()
{
	InitWindow(800, 600, "Gravity");
	SetWindowMonitor(0);
}

static Vector2 WorldToScreen(Vector2 worldPos)
{
	float zoomScale = ((float)GetScreenHeight() / (2.0f * astroUnit)) * camera.zoom;
	Vector2 screenCenter = Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
	Vector2 offset = (worldPos - camera.center) * zoomScale;
	return screenCenter + offset;
}

static int CalcSegments(float screenRadius)
{
    if (screenRadius < 1.0f) return 6;
    float angle = acosf(1.0f - 1.0f / screenRadius);
    int segments = (int)(PI / angle) + 1;
    return segments < 6 ? 6 : segments;
}

void Draw() 
{
	float aspect = (float)GetScreenWidth() / (float)GetScreenHeight();
	BeginDrawing();
	
	ClearBackground(BLACK);
	
	float orbitRadiusScreen = 300.0f * camera.zoom;
	int segments = CalcSegments(orbitRadiusScreen);
	
	//DrawRing(WorldToScreen(Vector2Zero()), 299.5f * camera.zoom, 300.5f * camera.zoom, 0, 360, segments, WHITE);
	DrawCircleLinesV(WorldToScreen(Vector2Zero()), 300 * camera.zoom, WHITE);
	
	for (int i = 0; i < planets.size(); i++) 
	{
		DrawCircleV(WorldToScreen(planets[i].pos), planets[i].radius, planets[i].color);
	}
	
	EndDrawing();
}