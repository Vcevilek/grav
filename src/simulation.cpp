#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "data.h"
#include "simulation.h"

Planet planets[9];
bool followEarth = false;

void Start() 
{
	Planet sun;
	sun.pos = Vector2(0.0f, 0.0f);
	sun.mass = 1.989e30f;
	sun.radius = 25.0f;
	sun.color = YELLOW;
	
	Planet mercury;
	mercury.pos = Vector2(-0.39f * astroUnit, 0.0f);
	mercury.mass = 3.285e23f;
	mercury.vel = Vector2(0.0f, 47900.0f);
	mercury.radius = 3.0f;
	mercury.color = GRAY;
	
	Planet venus;
	venus.pos = Vector2(-0.72f * astroUnit, 0.0f);
	venus.mass = 4.867e24f;
	venus.vel = Vector2(0.0f, 35000.0f);
	venus.radius = 5.0f;
	venus.color = ORANGE;
	
	Planet earth;
	earth.pos = Vector2(-astroUnit, 0.0f);
	earth.mass = 5.972e24f;
	earth.vel  = Vector2(0.0f, 29783.0f);
	earth.radius = 6.0f;
	earth.color = BLUE;
	
	Planet mars;
	mars.pos = Vector2(-1.524f * astroUnit, 0.0f);
	mars.mass = 6.39e23f;
	mars.vel = Vector2(0.0f, 24077.0f);
	mars.radius = 4.0f;
	mars.color = RED;
	
	Planet jupiter;
	jupiter.pos = Vector2(-5.2f * astroUnit, 0.0f);
	jupiter.mass = 1.89813e27;
	jupiter.vel = Vector2(0.0f, 13100.0f);
	jupiter.radius = 16.0f;
	jupiter.color = BEIGE;
	
	Planet saturn;
	saturn.pos = Vector2(-9.58f * astroUnit, 0.0f);
	saturn.mass = 5.683e26f;
	saturn.vel = Vector2(0.0f, 9700.0f);
	saturn.radius = 12.0f;
	saturn.color = YELLOW;
	
	Planet uranus;
	uranus.pos = Vector2(-19.22f * astroUnit, 0.0f);
	uranus.mass = 8.681e25f;
	uranus.vel = Vector2(0.0f, 6800.0f);
	uranus.radius = 11.0f;
	uranus.color = SKYBLUE;
	
	Planet neptune;
	neptune.pos = Vector2(-30.07 * astroUnit, 0.0f);
	neptune.mass = 1.024e26f;
	neptune.vel = Vector2(0.0f, 5400.0f);
	neptune.radius = 9.0f;
	neptune.color = DARKBLUE;

	planets[Sun] = sun;
	planets[Mercury] = mercury;
	planets[Venus] = venus;
	planets[Earth] = earth;
	planets[Mars] = mars;
	planets[Jupiter] = jupiter;
	planets[Saturn] = saturn;
	planets[Uranus] = uranus;
	planets[Neptune] = neptune;
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
	
	float panSpeed = (float)(astroUnit * delta / camera.zoom);
	if (IsKeyDown(KEY_LEFT))  camera.center.x -= panSpeed;
	if (IsKeyDown(KEY_RIGHT)) camera.center.x += panSpeed;
	if (IsKeyDown(KEY_UP))    camera.center.y -= panSpeed;
	if (IsKeyDown(KEY_DOWN))  camera.center.y += panSpeed;

	if (IsKeyDown(KEY_EQUAL)) camera.zoom *= 1.0002f;
	if (IsKeyDown(KEY_MINUS)) camera.zoom *= 0.9998f;
	if (IsKeyDown(KEY_ENTER)) followEarth = !followEarth;
	
	if (followEarth)
	{
		camera.center = planets[Earth].pos;
	}
	
	IntegrateForces(delta * 86400.0f * 30.0f);
}

void IntegrateForces(float delta)
{
	for (int i = 0; i < std::size(planets); i++) 
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
