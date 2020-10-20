#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

struct PhysBody3D;
struct PhysMotor3D;

class myMesh;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	void Draw();
	bool CleanUp();


public:

	Timer game_timer;
	Plane p;

	std::vector<myMesh> meshes;
};
