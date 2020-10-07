#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"

#include "Libraries/Glew/include/GL/glew.h"
#include "Libraries/SDL/include/SDL_opengl.h"

#include "Libraries/ImGui/imgui.h"
#include "Libraries/ImGui/imgui_internal.h"
#include "Libraries/ImGui/imgui_impl_sdl.h"
#include "Libraries/ImGui/imgui_impl_opengl3.h"

#include <GL/glew.h> 


ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Init()
{
	//IMGUI_CHECKVERSION();

	return true;
}

bool ModuleUI::Start()
{

	return true;
}

update_status ModuleUI::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleUI::CleanUp()
{

	return true;
}