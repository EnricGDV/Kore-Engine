#include "Application.h"
#include "WindowHierarchy.h"
#include "GameObject.h"

WindowHierarchy::WindowHierarchy() : Window()
{
}

WindowHierarchy::~WindowHierarchy()
{
}

bool WindowHierarchy::Start() 
{
	return true;
}

bool WindowHierarchy::Draw() 
{
	if (App->ui->hierarchyIsActive)
	{
		ImGui::Begin("Hierarchy", &App->ui->hierarchyIsActive);

		if (ImGui::Checkbox("", &App->scene_intro->rootGameObject->selected))
		{
			for (int i = 0; i < App->scene_intro->rootGameObject->children.size(); i++)
			{
				App->scene_intro->rootGameObject->children[i]->selected = false;
			}
		}
		ImGui::SameLine();
		if (App->scene_intro->rootGameObject->selected)
		{
			App->scene_intro->selectedGameObject = App->scene_intro->rootGameObject;
			App->scene_intro->isSelected = true;
		}
			
		if (ImGui::CollapsingHeader(App->scene_intro->rootGameObject->name.c_str()))
		{
			if (App->scene_intro->rootGameObject->children.size() > 0)
			{
				ImGui::Indent();
				for (int i = 0; i < App->scene_intro->rootGameObject->children.size(); i++)
				{
					if (App->scene_intro->rootGameObject->children.size() > 0 )
					{							
						if(ImGui::Checkbox(App->scene_intro->rootGameObject->children[i]->name.c_str(), &App->scene_intro->rootGameObject->children[i]->selected))
						{
							App->scene_intro->rootGameObject->selected = false;
							for (int j = 0; j < App->scene_intro->rootGameObject->children.size(); j++)
							{
								if(j != i)
									App->scene_intro->rootGameObject->children[j]->selected = false;
							}
						}
						if (App->scene_intro->rootGameObject->children[i]->selected)
						{
							App->scene_intro->selectedGameObject = App->scene_intro->rootGameObject->children[i];
							App->scene_intro->isSelected = true;
						}

						//if (App->scene_intro->rootGameObject->children[i]->children.size() > 0)
						//{
						//	ImGui::Indent();
						//	for (int j = 0; j < App->scene_intro->rootGameObject->children[i]->children.size(); j++)
						//	{

						//		if (ImGui::Checkbox(App->scene_intro->rootGameObject->children[i]->children[j]->name.c_str(), &App->scene_intro->rootGameObject->children[i]->children[j]->selected))
						//		{
						//			App->scene_intro->selectedGameObject = App->scene_intro->rootGameObject->children[i]->children[j];
						//		}
						//	}
						//	ImGui::Unindent();
						//}
					}
				}
			}
		} 


		ImGui::End();
	}
	return true;
}

bool WindowHierarchy::CleanUp()
{
	return true;
}