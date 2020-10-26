#include "Application.h"
#include "WindowMenuBar.h"

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
	ImGui::EndMainMenuBar();

	return true;
}

bool WindowMenuBar::CleanUp()
{
	return true;
}