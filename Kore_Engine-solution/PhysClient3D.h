#pragma once

#include "PhysBody3D.h"
#include "Primitive.h"
#include "glmath.h"

struct PhysBody3D;
class Application;

enum class state
{
	Waiting,
	Riding,
	Done
};

struct PhysClient3D : public PhysBody3D
{
public:
	PhysClient3D(PhysBody3D body);
	~PhysClient3D();

	Cube* client;
	state st;

	void Render();
	void HopOn();
	void HopOut();

private:
	Application* App;
};