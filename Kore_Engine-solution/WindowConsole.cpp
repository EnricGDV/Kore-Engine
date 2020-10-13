#include "Application.h"
#include "WindowConsole.h"
#include "Libraries/ImGui/imgui.h"


WindowConsole::WindowConsole() : Window()
{}

WindowConsole::~WindowConsole()
{}

bool WindowConsole::Start()
{
	return true;
}

bool WindowConsole::Draw()
{
	return true;
}

bool WindowConsole::CleanUp()
{
	return true;
}