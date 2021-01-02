#include "ModuleUI.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleUI::~ModuleUI()
{

}

bool ModuleUI::Init() 
{
	bool ret = true;
	return ret;
}
bool ModuleUI::Start()
{
	bool ret = true;
	return ret;
}
update_status ModuleUI::Update(float dt)
{
	return UPDATE_CONTINUE;
}
update_status ModuleUI::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}
bool ModuleUI::CleanUp()
{
	bool ret = true;
	return ret;
}