#include "ComponentMesh.h"
#include "GameObject.h"
#include "Libraries/Glew/include/GL/glew.h"

ComponentMesh::ComponentMesh(GameObject* owner) :Component(owner, Type::MESH)
{
	_vertices = new float3[num_vertices];
}

ComponentMesh::~ComponentMesh()
{

}


bool ComponentMesh::Update()
{


	bbox.SetNegativeInfinity();
	bbox.Enclose(_vertices, num_vertices);

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
		float vX = bbox.Edge(i).a.x;
		float vY = bbox.Edge(i).a.y;
		float vZ = bbox.Edge(i).a.z;

		float v2X = bbox.Edge(i).b.x;
		float v2Y = bbox.Edge(i).b.y;
		float v2Z = bbox.Edge(i).b.z;

		glVertex3f(vX, vY, vZ);
		glVertex3f(v2X, v2Y, v2Z);
	}

	glEnd();
	glColor3f(1, 1, 1);
}