#pragma once
#include "Module.h"
#include "Globals.h"

struct PhysBody3D;
struct PhysMotor3D;

class myMesh;
class myTexture;
class GameObject;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	void Draw();
	bool CleanUp();

	GameObject* CreateGameObject();

public:

	Timer game_timer;

	std::vector<myMesh> meshes;
	std::vector<myTexture> textures;

	std::vector<GameObject*> gameObjects;

};
