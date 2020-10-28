#include "Application.h"
#include "WindowInspector.h"

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

		ImGui::End();
	}
	return true;
}

bool WindowInspector::CleanUp()
{
	return true;
}