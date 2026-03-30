#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>

#define gravConst 6.6743e-11
#define astroUnit 1.496e11

struct Planet 
{
	Vector2 pos = Vector2Zero();
	Vector2 vel = Vector2Zero();
	Vector2 accel = Vector2Zero();
	
	float mass = 1.0f;
	float radius = 10.0f;
	Color color = RED;
};

struct AstroCam 
{
	Vector2 center = Vector2Zero();
	float zoom = 1.0f;
};

enum 
{
	Sun,
	Mercury,
	Venus,
	Earth,
	Mars,
	Jupiter,
	Saturn,
	Uranus,
	Neptune,
};

extern Planet planets[9];
extern AstroCam camera;