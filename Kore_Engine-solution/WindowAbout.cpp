#include "Application.h"
#include "WindowAbout.h"


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

	return true;
}

bool WindowAbout::CleanUp()
{
	return true;
}