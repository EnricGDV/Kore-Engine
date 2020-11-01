#include "Application.h"
#include "WindowInspector.h"
#include "ModuleSceneIntro.h"
#include "GameObject.h"
#include "Importer.h"
WindowInspector::WindowInspector() : Window()
{

}

WindowInspector::~WindowInspector()
{

}


bool WindowInspector::Start()
{
	return true;
}

bool WindowInspector::Draw()
{
	if (App->ui->inspectorIsActive)
	{
		ImGui::Begin("Inspector", &App->ui->inspectorIsActive);

		if (App->scene_intro->isSelected)
		{
			ImGui::Text("Name: ");  ImGui::SameLine();
			ImGui::TextColored({ 1.0f, 0.f, 0.7f, 1.f }, "%s", App->scene_intro->selectedGameObject->name.c_str(), App->scene_intro->selectedGameObject->name.max_size());
			ImGui::Checkbox("Active", &App->scene_intro->selectedGameObject->active);
		}

		ImGui::Spacing();

		if (ImGui::CollapsingHeader("Transform"))
		{
			if (App->scene_intro->isSelected)
			{
				
			}
		}

		ImGui::Spacing();

		if (App->scene_intro->isSelected)
		{
			for (int i = 0; i < App->scene_intro->selectedGameObject->components.size(); i++)
			{
				if (App->scene_intro->selectedGameObject->components[i]->type == Type::MESH)
				{
					if (ImGui::CollapsingHeader("Mesh"))
					{
						ImGui::Checkbox("Active", &App->scene_intro->selectedGameObject->mesh->isActive); ImGui::SameLine();
						if (ImGui::Button("Delete Component"))
						{
							App->scene_intro->selectedGameObject->components[i]->Disable();
							App->scene_intro->meshes.erase(App->scene_intro->meshes.begin() + i);
						}

						ImGui::Text("Num Vertices: "); ImGui::SameLine(); ImGui::TextColored({ 1.0f, 0.f, 0.7f, 1.f }, "%d", App->scene_intro->selectedGameObject->mesh->num_vertices);
						ImGui::Text("Num Indices: "); ImGui::SameLine(); ImGui::TextColored({ 1.0f, 0.f, 0.7f, 1.f }, "%d", App->scene_intro->selectedGameObject->mesh->num_indices);
						ImGui::Text("Num Faces: "); ImGui::SameLine(); ImGui::TextColored({ 1.0f, 0.f, 0.7f, 1.f }, "%d", App->scene_intro->selectedGameObject->mesh->num_faces);


						ImGui::Checkbox("Show Normals", &App->renderer3D->drawNormals);
					}
				}

				ImGui::Spacing();

				if (App->scene_intro->selectedGameObject->components[i]->type == Type::MATERIAL)
				{
					if (ImGui::CollapsingHeader("Material"))
					{
						ImGui::Checkbox("Active", &App->scene_intro->selectedGameObject->material->isActive); ImGui::SameLine();

						if (ImGui::Button("Delete Component"))
						{
							App->scene_intro->selectedGameObject->components[i]->Disable();
							if (App->scene_intro->textures.size() > 0)
								App->scene_intro->textures.erase(App->scene_intro->textures.begin());
						}

						if (App->scene_intro->selectedGameObject->material->isActive)
						{

							ImGui::Text("Path: "); ImGui::SameLine(); ImGui::TextColored({ 1.0f, 0.f, 0.7f, 1.f }, "%s", App->scene_intro->selectedGameObject->material->path);

							ImGui::Text("Size: "); ImGui::SameLine(); ImGui::TextColored({ 1.0f, 0.f, 0.7f, 1.f }, "%dx%d", App->scene_intro->selectedGameObject->material->width, App->scene_intro->selectedGameObject->material->height);
						}
						

						ImGui::Checkbox("Checker Texture", &App->scene_intro->selectedGameObject->material->isCheckers);
					}
				}
			}

		}
		
		ImGui::End();
	}
	return true;
}

bool WindowInspector::CleanUp()
{
	return true;
}