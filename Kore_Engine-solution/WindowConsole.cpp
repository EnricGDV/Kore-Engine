#include "Application.h"
#include "WindowConsole.h"


WindowConsole::WindowConsole() : Window()
{
}

WindowConsole::~WindowConsole()
{
}

bool WindowConsole::Start()
{
	App->ConsoleLog("Creating Console Window");

	return true;
}

bool WindowConsole::Draw()
{
	if (App->ui->consoleIsActive)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5, 2));
		ImGui::Begin("Console", &App->ui->consoleIsActive);

		for (int i = 0; i < App->vector_log.size(); ++i)
		{
			ImGui::Text(App->vector_log[i].data());
		}

		if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
		{
			ImGui::SetScrollHereY(1.0f);
		}

		ScrollToBottom = false;
		ImGui::End();
		ImGui::PopStyleVar();
	}
	return true;
}

bool WindowConsole::CleanUp()
{
	return true;
}