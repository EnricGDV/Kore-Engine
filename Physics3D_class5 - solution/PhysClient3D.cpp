#include "PhysClient3D.h"
#include "Application.h"
#include "Globals.h"
#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"


// ----------------------------------------------------------------------------
PhysClient3D::PhysClient3D(PhysBody3D body) : PhysBody3D(body) , st(state::Waiting)
{
}

// ----------------------------------------------------------------------------
PhysClient3D::~PhysClient3D()
{
	delete client;
}

// ----------------------------------------------------------------------------
void PhysClient3D::Render()
{
	
	if (st == state::Waiting)
	{
		client->color = Red;
	}
	else if (st == state::Riding)
	{
		client->SetPos(App->player->pos.x, App->player->pos.y + 2, App->player->pos.z);
	}
	else if (st == state::Done)
	{
		client->color = Green;
	}

	client->Render();
}

void PhysClient3D::HopOn()
{
	st = state::Riding;
}

void PhysClient3D::HopOut()
{
	st = state::Done;
	client->SetPos(App->player->pos.x - 3, App->player->pos.y, App->player->pos.z);
}