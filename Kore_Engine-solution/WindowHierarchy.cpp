#include "Application.h"
#include "WindowHierarchy.h"

WindowHierarchy::WindowHierarchy() : Window()
{
}

WindowHierarchy::~WindowHierarchy()
{
}

bool WindowHierarchy::Start() 
{
	return true;
}

bool WindowHierarchy::Draw() 
{
	if (App->ui->hierarchyIsActive)
	{
		ImGui::Begin("Hierarchy", &App->ui->hierarchyIsActive);

		ImGui::End();
	}
	return true;
}

bool WindowHierarchy::CleanUp()
{
	return true;
}