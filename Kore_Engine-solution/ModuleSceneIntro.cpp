#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Importer.h"
#include "GameObject.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;


	Importer::Debug();
	meshes = Importer::LoadMeshes("Assets/Models/street2.fbx");

	//textures.push_back(Importer::LoadTexture("Assets/Textures/blending_transparent_window.png"));
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		gameObjects[i]->material->width = App->scene_intro->textures.back().width;
		gameObjects[i]->material->height = App->scene_intro->textures.back().height;
		gameObjects[i]->material->path = App->scene_intro->textures.back().path;
		gameObjects[i]->material->isActive = true;
	}
	



	game_timer.Start();


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	Importer::CleanDebug();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::Draw()
{
	
}

GameObject* ModuleSceneIntro::CreateGameObject()
{
	std::string GOName = "GameObject "; 
	GOName.append(std::to_string(gameObjects.size()));

	GameObject* go = new GameObject(GOName);

	gameObjects.push_back(go);
	return go;
}

void ModuleSceneIntro::Save()
{
	char* buffer;
	uint64 size;

	string texturePath = TEXTURES_PATH;
	texturePath.append("CurrentTexture.ket");

	size = Importer::SaveTexture(textures.end()._Ptr, &buffer);

	if (size > 0)
	{
		App->file_system->Save(texturePath.c_str(), buffer, size);
	}

	
}