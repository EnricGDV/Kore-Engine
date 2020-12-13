#include "ComponentMesh.h"
#include "GameObject.h"
#include "Libraries/Glew/include/GL/glew.h"

ComponentMesh::ComponentMesh(GameObject* owner) :Component(owner, Type::MESH)
{

}

ComponentMesh::~ComponentMesh()
{

}


bool ComponentMesh::Update()
{
	obb = bbox;
	obb.Transform(owner->transform->GetMatrix());

	Gbbox.SetNegativeInfinity();
	Gbbox.Enclose(obb);

	return true;
}

math::AABB ComponentMesh::GetAABB()
{
	return bbox;
}

void ComponentMesh::DrawAABB()
{
	glLineWidth(1.5f);
	glBegin(GL_LINES);
	glColor3f(1, 0, 1);

	for (uint i = 0; i < 12; i++)
	{
		float vX = Gbbox.Edge(i).a.x;
		float vY = Gbbox.Edge(i).a.y;
		float vZ = Gbbox.Edge(i).a.z;

		float v2X = Gbbox.Edge(i).b.x;
		float v2Y = Gbbox.Edge(i).b.y;
		float v2Z = Gbbox.Edge(i).b.z;

		glVertex3f(vX, vY, vZ);
		glVertex3f(v2X, v2Y, v2Z);
	}

	glEnd();
	glColor3f(1, 1, 1);
}