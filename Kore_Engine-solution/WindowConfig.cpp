#include "Application.h"
#include "WindowConfig.h"

WindowConfig::WindowConfig() : Window()
{

}

WindowConfig::~WindowConfig()
{
}

bool WindowConfig::Start()
{
	App->ui->brightness = 1.f;
	App->ui->windowWidth = SCREEN_WIDTH * SCREEN_SIZE;
	App->ui->windowHeight = SCREEN_HEIGHT * SCREEN_SIZE;

	return true;
}

bool WindowConfig::Draw()
{

	// Show Configuration
	if (App->ui->configIsActive)
	{

		ImGui::Begin("Configuration", &App->ui->configIsActive);

		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("Set Defaults"))
			{

			}

			if (ImGui::MenuItem("Save"))
			{

			}

			if (ImGui::MenuItem("Load"))
			{

			}
			ImGui::EndMenu();
		}

		ImGui::Spacing();

		if (ImGui::CollapsingHeader("Application"))
		{
			ImGui::InputText("Engine Name", App->ui->textname, 32);
			ImGui::InputText("Organization", App->ui->textorganization, 32);
			ImGui::SliderInt("Max FPS", &App->max_fps, 0, 200);
			ImGui::Spacing();

			char title[25];
			sprintf_s(title, 25, "Framerate %.1f", App->fps[App->fps.size() - 1]);
			ImGui::PlotHistogram("##framerate", &App->fps[0], App->fps.size(), 0, title, 0.0f, 200.0f, ImVec2(310, 100));
			sprintf_s(title, 25, "Milliseconds %.1f", App->ms[App->ms.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &App->ms[0], App->ms.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Spacing();
		}
		if (ImGui::CollapsingHeader("Window"))
		{
			ImGui::Checkbox("Active", &App->input->quit);
			ImGui::SliderFloat("Brightness", &App->ui->brightness, 0.0f, 1.0f);
			ImGui::SliderInt("Width", &App->ui->windowWidth, 0.0f, 1920);
			ImGui::SliderInt("Height", &App->ui->windowHeight, 0.0f, 1080);
			ImGui::Checkbox("Fullscreen", &App->ui->fullscreen);
			ImGui::SameLine();
			ImGui::Checkbox("Resizable", &App->ui->resizable);
			ImGui::Checkbox("Borderless", &App->ui->borderless);
			ImGui::SameLine();
			ImGui::Checkbox("Full Desktop", &App->ui->fulldesktop);
			ImGui::Spacing();

		}
		if (ImGui::CollapsingHeader("Renderer"))
		{
			ImGui::Checkbox("Depth Test", &App->renderer3D->switchDepthTest);
			ImGui::SameLine();
			ImGui::Checkbox("Cull Face", &App->renderer3D->switchCullFace);
			ImGui::Checkbox("Lighting", &App->renderer3D->switchLighting);
			ImGui::SameLine();
			ImGui::Checkbox("Textures 2D", &App->renderer3D->switchGlTexture2D);
			ImGui::Checkbox("Wireframe", &App->renderer3D->isWireframe);
			ImGui::Spacing();
		}
		if (ImGui::CollapsingHeader("File System"))
		{

		}
		if (ImGui::CollapsingHeader("Input"))
		{

		}
		if (ImGui::CollapsingHeader("Hardware"))
		{

		}



		ImGui::End();

	}
	return true;
}

bool WindowConfig::CleanUp()
{
	return true;
}
