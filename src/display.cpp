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
	DrawFPS(0, 0);
	
	float orbitRadiusScreen = 300.0f * camera.zoom;
	int segments = CalcSegments(orbitRadiusScreen);
	
	//DrawRing(WorldToScreen(Vector2Zero()), 299.5f * camera.zoom, 300.5f * camera.zoom, 0, 360, segments, WHITE);
	float orbits[] = {0.39f, 0.72f, 1.0f, 1.524f, 5.2f, 9.58f, 19.22f, 30.07f};
	for (float orbit : orbits)
	{
		DrawCircleLinesV(WorldToScreen(Vector2Zero()), orbit * 300.0f * camera.zoom, WHITE);
	}
	
	for (int i = 0; i < std::size(planets); i++) 
	{
		DrawCircleV(WorldToScreen(planets[i].pos), planets[i].radius * camera.zoom, planets[i].color);
		//else DrawCircleV(WorldToScreen(planets[i].pos), planets[i].radius, planets[i].color);
	}
	
	EndDrawing();
}