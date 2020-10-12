#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleInput.h"

#include <GL/glew.h>

#include "Libraries/ImGui/imgui.h"
#include "Libraries/ImGui/imgui_impl_sdl.h"
#include "Libraries/ImGui/imgui_impl_opengl3.h"
#include "Libraries/ImGui/imgui_internal.h"




ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Init()
{
	IMGUI_CHECKVERSION();

	return true;
}

bool ModuleUI::Start()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsLight();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init("#version 130");

	font = io.Fonts->AddFontDefault();
    IM_ASSERT(font != NULL);

	return true;
}

update_status ModuleUI::PreUpdate(float dt)
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

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
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Configuration");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Welcome to Kore Engine");               // Display some text (you can use a format strings too)

		ImGui::SameLine();
		if (ImGui::Button("Close App"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			App->input->quit = true;

		ImGui::Checkbox("Show Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&Pink); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	return UPDATE_CONTINUE;
}


update_status ModuleUI::PostUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}

void ModuleUI::Draw()
{
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Called before quitting
bool ModuleUI::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}