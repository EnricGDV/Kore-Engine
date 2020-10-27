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
	menubar = new WindowMenuBar();
	config = new WindowConfig();
	about = new WindowAbout();
	hierarchy = new WindowHierarchy();
	inspector = new WindowInspector();

	//add to window list
	windows.push_back(console);
	windows.push_back(menubar);
	windows.push_back(config);
	windows.push_back(about);
	windows.push_back(hierarchy);
	windows.push_back(inspector);


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