#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleWindow.h"

#include <GL/glew.h>

#include "Libraries/ImGui/imgui.h"
#include "Libraries/ImGui/imgui_impl_sdl.h"
#include "Libraries/ImGui/imgui_impl_opengl3.h"




ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Init()
{

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsLight();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init("#version 130");

	font = io.Fonts->AddFontDefault();
	IM_ASSERT(font != NULL);

	textname = "Kore Engine";
	textorganization = "UPC CITM";

	console = new WindowConsole();

	//add to window list
	windows.push_back(console);


	return true;
}

bool ModuleUI::Start()
{
	bool ret = true;

	for (std::list<Window*>::const_iterator it = windows.begin(); it != windows.end(); it++)
	{
		ret = (*it)->Start();
	}

	return ret;

}

update_status ModuleUI::PreUpdate(float dt)
{

	// Poll and handle events (inputs, window resize, etc.)
	// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
	// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
	// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
	// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)
			return UPDATE_CONTINUE;
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(App->window->window))
			return UPDATE_CONTINUE;
	}

	//// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();



	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	//// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (demoIsActive)
		ImGui::ShowDemoWindow(&demoIsActive);

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
		ImGui::Checkbox("Console", &consoleIsActive);
		ImGui::Checkbox("Configuration", &configIsActive);
		ImGui::Checkbox("Demo Window", &demoIsActive);      // Edit bools storing our window open/close state

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
			aboutIsActive = true;

		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	if (aboutIsActive)
	{
		ImGui::Begin("About Kore Engine");
		ImGui::Text("Kore Engine v0.3");
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Text("By Enric-G. Duran and Clara Ratera. Supervised by prof. Marc Garrigo");
		ImGui::Text("3D Engine for the Game Engines Subject at CITM, UPC for educational purposes.");
		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::MenuItem("Go to the GitHub page"))
			App->RequestBrowser("https://github.com/EnricGDV/Kore-Engine");
		ImGui::Spacing();

		ImGui::Text("3rd Party Libraries used:");
		ImGui::BulletText("SDL 2.0.12");
		ImGui::BulletText("Glew 2.1.0");
		ImGui::BulletText("ImGui 1.79");
		ImGui::BulletText("OpenGL 3.1");
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::Text("License:");
		ImGui::Spacing();
		ImGui::Text("MIT License");
		ImGui::Spacing();
		ImGui::Text("Copyright (c) 2020 EnricGDV");
		ImGui::Spacing();
		ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files(the 'Software'), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and /or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions : ");
		ImGui::Spacing();
		ImGui::Text("The above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.");
		ImGui::Spacing();
		ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.");

		ImGui::End();
	}



	// Show Configuration
	if (configIsActive)
	{

		ImGui::Begin("Configuration");

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
			ImGui::InputText("Engine Name", textname, 32);
			ImGui::InputText("Organization", textorganization, 32);
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
			ImGui::SliderFloat("Brightness", &App->renderer3D->brightness, 0.0f, 1.0f);
			ImGui::SliderInt("Width", &App->window->width, 0.0f, 1920);
			ImGui::SliderInt("Height", &App->window->height, 0.0f, 1080);
			ImGui::Checkbox("Fullscreen", &App->window->fullscreen);
			ImGui::SameLine();
			ImGui::Checkbox("Resizable", &App->window->resizable);
			ImGui::Checkbox("Borderless", &App->window->borderless);
			ImGui::SameLine();
			ImGui::Checkbox("Full Desktop", &App->window->fulldesktop);
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
	

	
	

	return UPDATE_CONTINUE;
}


update_status ModuleUI::PostUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}

bool ModuleUI::Draw()
{

	bool ret = true;

	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		ImGui_ImplSDL2_ProcessEvent(&ev);
	}

	//Draw Windows List
	for (std::list<Window*>::const_iterator it = windows.begin(); it != windows.end(); it++)
	{
		ret = (*it)->Draw();
	}

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return ret;
}

// Called before quitting
bool ModuleUI::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}