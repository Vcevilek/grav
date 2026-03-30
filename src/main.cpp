#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>

#define gravConst 6.6743e-11
#define astroUnit 1.496e11

struct Body 
{
	Vector2 pos = Vector2Zero();
	Vector2 vel = Vector2Zero();
	Vector2 accel = Vector2Zero();
	
	float mass = 1.0f;
	float radius = 10.0f;
	Color color = RED;
};

std::vector<Body> planets;

#pragma region Functions
void Start();
void Update(float delta);
void Draw();
void IntegrateForces(float delta);
Vector2 GetGravity(Body bodyA, Body bodyB);
#pragma endregion

int main() 
{
	Start();
	
	while(!WindowShouldClose())
		Update(GetFrameTime());
	
	return 0;
}

void Start() 
{
	Body sun;
	sun.pos = Vector2(0.0f, 0.0f);
	sun.mass = 1.989e30f;
	sun.radius = 25.0f;
	sun.color = YELLOW;
	
	Body earth;
	earth.pos = Vector2(astroUnit, 0.0f);
	earth.mass = 5.972e24f;
	earth.vel  = Vector2(0.0f, 29783.0f);
	earth.color = GREEN;
	
	planets.push_back(sun);
	planets.push_back(earth);
	
	InitWindow(800, 600, "Gravity");
	SetWindowMonitor(0);
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
	
	IntegrateForces(delta * 86400.0f * 30.0f);
	Draw();
}

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

void IntegrateForces(float delta)
{
	for (int i = 0; i < planets.size(); i++) 
	{
		planets[i].vel += planets[i].accel * delta;
		planets[i].pos += planets[i].vel * delta;
	}
}

Vector2 GetGravity(Body bodyA, Body bodyB)
{
	if (bodyA.pos == bodyB.pos) return Vector2Zero();
	Vector2 offset = bodyB.pos - bodyA.pos;
	
	Vector2 dir = Vector2Normalize(offset);
	float radius2 = Vector2LengthSqr(offset);
	if (radius2 < 1e-2) return Vector2Zero();
	
	float force = gravConst * bodyA.mass * bodyB.mass / radius2;
	
	return dir * force;
}