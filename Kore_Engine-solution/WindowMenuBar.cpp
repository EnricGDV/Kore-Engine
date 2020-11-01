#include "Application.h"
#include "WindowMenuBar.h"
#include "Importer.h"

WindowMenuBar::WindowMenuBar() : Window ()
{
}

WindowMenuBar::~WindowMenuBar()
{
}

bool WindowMenuBar::Start()
{
	return true;
}

bool WindowMenuBar::Draw()
{

	// Show Bar
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Quit (ESC)"))
			App->input->quit = true;

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("View"))
	{
		ImGui::Checkbox("Console", &App->ui->consoleIsActive);
		ImGui::Checkbox("Configuration", &App->ui->configIsActive);
		ImGui::Checkbox("Hierarchy", &App->ui->hierarchyIsActive);
		ImGui::Checkbox("Inspector", &App->ui->inspectorIsActive);
		ImGui::Checkbox("About", &App->ui->aboutIsActive);
		ImGui::Checkbox("Demo Window", &App->ui->demoIsActive);      // Edit bools storing our window open/close state

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("Documentation"))
			App->RequestBrowser("https://github.com/EnricGDV/Kore-Engine/wiki");
		if (ImGui::MenuItem("Download latest"))
			App->RequestBrowser("https://github.com/EnricGDV/Kore-Engine/releases");
		if (ImGui::MenuItem("Report a bug"))
			App->RequestBrowser("https://github.com/EnricGDV/Kore-Engine/issues");
		if (ImGui::MenuItem("About"))
			App->ui->aboutIsActive = true;

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Primitives"))
	{
		if (ImGui::MenuItem("Cube"))
		{
			App->scene_intro->meshes = Importer::LoadMeshes("Assets/Models/Primitives/Cube.FBX");
			App->scene_intro->isSelected = false;
			App->scene_intro->selectedGameObject = nullptr;
			App->renderer3D->GenerateMeshes();
		}
		if (ImGui::MenuItem("Sphere"))
		{
			App->scene_intro->meshes = Importer::LoadMeshes("Assets/Models/Primitives/Sphere.FBX");
			App->scene_intro->isSelected = false;
			App->scene_intro->selectedGameObject = nullptr;
			App->renderer3D->GenerateMeshes();
		}
		if (ImGui::MenuItem("Pyramid"))
		{
			App->scene_intro->meshes = Importer::LoadMeshes("Assets/Models/Primitives/Pyramid.FBX");
			App->scene_intro->isSelected = false;
			App->scene_intro->selectedGameObject = nullptr;
			App->renderer3D->GenerateMeshes();
		}
		if (ImGui::MenuItem("Cylinder"))
		{
			App->scene_intro->meshes = Importer::LoadMeshes("Assets/Models/Primitives/Cylinder.FBX");
			App->scene_intro->isSelected = false;
			App->scene_intro->selectedGameObject = nullptr;
			App->renderer3D->GenerateMeshes();
		}

		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	return true;
}

bool WindowMenuBar::CleanUp()
{
	return true;
}