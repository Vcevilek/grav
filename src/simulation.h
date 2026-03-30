#pragma once
#include <raylib.h>
#include "data.h"

void Start();
void Update(float delta);
void IntegrateForces(float delta);
Vector2 GetGravity(Planet bodyA, Planet bodyB);