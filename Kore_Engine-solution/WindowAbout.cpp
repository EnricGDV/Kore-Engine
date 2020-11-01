#include "Application.h"
#include "WindowAbout.h"
#include "Libraries/DevIL/include/IL/il.h"
#include "Libraries/DevIL/include/IL/ilu.h"
#include "Libraries/DevIL/include/IL/ilut.h"
#include "Libraries/Assimp/include/version.h"

WindowAbout::WindowAbout() : Window()
{
}

WindowAbout::~WindowAbout()
{
}

bool WindowAbout::Start()
{
	return true;
}

bool WindowAbout::Draw()
{

	if (App->ui->aboutIsActive)
	{
		ImGui::Begin("About Kore Engine", &App->ui->aboutIsActive);
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
		
		SDL_version compiled;
		SDL_GetVersion(&compiled);
		ImGui::BulletText("SDL %d.%d.%d", compiled.major, compiled.minor, compiled.patch);
		ImGui::BulletText("Glew %s.%s.%s", glewGetString(GLEW_VERSION_MAJOR), glewGetString(GLEW_VERSION_MINOR), glewGetString(GLEW_VERSION_MICRO));
		ImGui::BulletText("ImGui %.5s", ImGui::GetVersion());
		ImGui::BulletText("OpenGL %.5s", glGetString(GL_VERSION));
		ImGui::BulletText("MathGeoLib 1.5");
		ImGui::BulletText("Assimp %d.%d.%d", aiGetVersionMajor(), aiGetVersionMinor(), aiGetVersionRevision());
		ImGui::BulletText("DevIL %d", IL_VERSION);
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

	return true;
}

bool WindowAbout::CleanUp()
{
	return true;
}