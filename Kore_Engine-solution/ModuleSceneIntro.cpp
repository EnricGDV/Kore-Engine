#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Importer.h"

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
	meshes = Importer::LoadMeshes("Assets/Models/bakerhouse.fbx");

	textures.push_back(Importer::LoadTexture("Assets/Textures/bakerhouse.png"));

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
