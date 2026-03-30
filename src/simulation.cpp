#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "data.h"
#include "simulation.h"

std::vector<Planet> planets;
bool followEarth = false;

void Start() 
{
	Planet sun;
	sun.pos = Vector2(0.0f, 0.0f);
	sun.mass = 1.989e30f;
	sun.radius = 25.0f;
	sun.color = YELLOW;
	
	Planet earth;
	earth.pos = Vector2(astroUnit, 0.0f);
	earth.mass = 5.972e24f;
	earth.vel  = Vector2(0.0f, 29783.0f);
	earth.color = GREEN;
	
	Planet moon;
	moon.pos = Vector2(1.00257 * astroUnit, 0.0f);
	moon.mass = 7.342e22f;
	moon.vel = Vector2(0.0f, 29783.0f + 1022.0f);
	moon.radius = 4.0f;
	moon.color = GRAY;
	
	planets.push_back(moon);
	planets.push_back(earth);
	planets.push_back(sun);
}

void Update(float delta) 
{
	for (auto& bodyA : planets) 
	{
		bodyA.accel = Vector2Zero();
		for (auto& bodyB : planets) 
		{
			bodyA.accel += GetGravity(bodyA, bodyB) / bodyA.mass;
		}
	}
	
	float panSpeed = (float)(astroUnit * delta);
	if (IsKeyDown(KEY_LEFT))  camera.center.x -= panSpeed;
	if (IsKeyDown(KEY_RIGHT)) camera.center.x += panSpeed;
	if (IsKeyDown(KEY_UP))    camera.center.y -= panSpeed;
	if (IsKeyDown(KEY_DOWN))  camera.center.y += panSpeed;

	if (IsKeyDown(KEY_EQUAL)) camera.zoom *= 1.0002f;
	if (IsKeyDown(KEY_MINUS)) camera.zoom *= 0.9998f;
	if (IsKeyDown(KEY_ENTER)) followEarth = !followEarth;
	
	if (followEarth)
	{
		camera.center = planets[1].pos;
	}
	
	IntegrateForces(delta * 86400.0f * 30.0f);
}

void IntegrateForces(float delta)
{
	for (int i = 0; i < planets.size(); i++) 
	{
		planets[i].vel += planets[i].accel * delta;
		planets[i].pos += planets[i].vel * delta;
	}
}

Vector2 GetGravity(Planet bodyA, Planet bodyB)
{
	if (bodyA.pos == bodyB.pos) return Vector2Zero();
	Vector2 offset = bodyB.pos - bodyA.pos;
	
	Vector2 dir = Vector2Normalize(offset);
	float radius2 = Vector2LengthSqr(offset);
	if (radius2 < 1e-2) return Vector2Zero();
	
	float force = gravConst * bodyA.mass * bodyB.mass / radius2;
	
	return dir * force;
}
