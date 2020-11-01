#include "Application.h"
#include "WindowInspector.h"
#include "ModuleSceneIntro.h"

WindowInspector::WindowInspector() : Window()
{

}

WindowInspector::~WindowInspector()
{

}


bool WindowInspector::Start()
{
	return true;
}

bool WindowInspector::Draw()
{
	if (App->ui->inspectorIsActive)
	{
		ImGui::Begin("Inspector", &App->ui->inspectorIsActive);
	
		if (ImGui::CollapsingHeader("Transform"))
		{
			
		}
		ImGui::End();
	}
	return true;
}

bool WindowInspector::CleanUp()
{
	return true;
}