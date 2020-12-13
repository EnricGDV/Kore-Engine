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
				App->scene_intro->Save();
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
			ImGui::Checkbox("Active", &App->window->active);
			ImGui::SliderFloat("Brightness", &App->ui->brightness, 0.0f, 1.0f);
			ImGui::SliderInt("Width", &App->ui->windowWidth, 640, 1920);
			ImGui::SliderInt("Height", &App->ui->windowHeight, 480, 1080);
			ImGui::Checkbox("Fullscreen", &App->ui->fullscreen); ImGui::SameLine(); ImGui::Checkbox("Resizable", &App->ui->resizable);
			ImGui::Checkbox("Borderless", &App->ui->borderless); ImGui::SameLine(); ImGui::Checkbox("Full Desktop", &App->ui->fulldesktop);
			ImGui::Spacing();

		}
		if (ImGui::CollapsingHeader("Renderer"))
		{
			ImGui::Checkbox("Depth Test", &App->renderer3D->switchDepthTest);
			ImGui::SameLine();
			ImGui::Checkbox("Cull Face", &App->renderer3D->switchCullFace);
			ImGui::Checkbox("Lighting", &App->renderer3D->switchLighting); ImGui::SameLine(); ImGui::Checkbox("Textures 2D", &App->renderer3D->switchGlTexture2D);
			ImGui::Checkbox("Wireframe", &App->renderer3D->isWireframe);
			ImGui::Spacing();
		}
		if (ImGui::CollapsingHeader("File System"))
		{

		}
		if (ImGui::CollapsingHeader("Input"))
		{
			ImGui::Checkbox("Active", &App->input->active);
			ImGui::Text("Mouse Position: "); ImGui::SameLine(); ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "%d, %d", App->input->GetMouseX(), App->input->GetMouseY());
			ImGui::Text("Mouse Motion: "); ImGui::SameLine(); ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "%d, %d", App->input->GetMouseXMotion(), App->input->GetMouseYMotion());
			ImGui::Text("Mouse Wheel: "); ImGui::SameLine(); ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "%d", App->input->GetMouseZ());
		}
		if (ImGui::CollapsingHeader("Hardware"))
		{
			SDL_version compiled;
			SDL_GetVersion(&compiled);

			ImGui::Checkbox("Active", &App->input->active);
			ImGui::Text("SDL Version: "); ImGui::SameLine(); ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "%d.%d.%d", compiled.major, compiled.minor, compiled.patch);
			ImGui::Separator();

			ImGui::Text("CPUs: "); ImGui::SameLine(); ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "%d   (Cache: %dkb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
			ImGui::Text("System RAM: "); ImGui::SameLine(); ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "%.1lfGb", round(SDL_GetSystemRAM() / 1024.f));

			ImGui::Text("Caps: "); ImGui::SameLine();
			if(SDL_Has3DNow()) ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "3DNow,"); ImGui::SameLine(); if (SDL_HasAVX())ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "AVX,"); ImGui::SameLine();
			if (SDL_HasAltiVec())ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "AltiVec,"); ImGui::SameLine(); if (SDL_HasMMX())ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "MMX,"); ImGui::SameLine();
			if (SDL_HasRDTSC())ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "RDTSC,"); if (SDL_HasSSE()) ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "SSE,"); ImGui::SameLine();
			if (SDL_HasSSE2())ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "SSE2,"); ImGui::SameLine(); if (SDL_HasSSE3())ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "SSE3,"); ImGui::SameLine();
			if (SDL_HasSSE41())ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "SSE41,"); ImGui::SameLine(); if (SDL_HasSSE42())ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "SSE42,");
			ImGui::Separator();

			GLint vram_budget = 0;
			glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &vram_budget);

			ImGui::Text("GPU: "); ImGui::SameLine(); ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "%s %s", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
			//ImGui::Text("Brand: "); ImGui::SameLine(); ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "%s %s", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
			//ImGui::Text("VRAM Budget: "); ImGui::SameLine(); ImGui::TextColored({ 1.f, 0.f, 0.7f, 1.f }, "%.1lfMb", round(vram_budget / 1024.f));
		}



		ImGui::End();

	}
	return true;
}

bool WindowConfig::CleanUp()
{
	return true;
}
