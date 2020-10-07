#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Black;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);

	chassis.color = info.color;

	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	Cube driver(0.5f, 0.5f, 0.5f);
    vehicle->getChassisWorldTransform().getOpenGLMatrix(&driver.transform);
	btVector3 d_offset(info.chassis_offset.x + 0.5f, info.chassis_offset.y + 0.5f, info.chassis_offset.z);
	d_offset = d_offset.rotate(q.getAxis(), q.getAngle());
	driver.transform.M[12] += d_offset.getX();
	driver.transform.M[13] += d_offset.getY();
	driver.transform.M[14] += d_offset.getZ();
	driver.color = Yellow;

	Cube line(info.chassis_size.x/4, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&line.transform);
	btVector3 l_offset(info.chassis_offset.x, info.chassis_offset.y + info.chassis_size.y / 50.0f, info.chassis_offset.z - info.chassis_size.z / 500.0f);
	l_offset = l_offset.rotate(q.getAxis(), q.getAngle());
	line.transform.M[12] += l_offset.getX();
	line.transform.M[13] += l_offset.getY();
	line.transform.M[14] += l_offset.getZ();
	line.color = Black;

	Cube rightwing(info.chassis_size.x / 100.0f, info.chassis_size.y*1.3f, info.chassis_size.z / 1.5f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&rightwing.transform);
	btVector3 rw_offset(info.chassis_offset.x - info.chassis_size.x / 2.3f, info.chassis_offset.y + info.chassis_size.y / 2.5f, info.chassis_offset.z - info.chassis_size.z / 6.0f);
	rw_offset = rw_offset.rotate(q.getAxis(), q.getAngle());
	rightwing.transform.M[12] += rw_offset.getX();
	rightwing.transform.M[13] += rw_offset.getY();
	rightwing.transform.M[14] += rw_offset.getZ();
	rightwing.color = info.color;

	Cube leftwing(info.chassis_size.x / 100.0f, info.chassis_size.y*1.3f, info.chassis_size.z / 1.5f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&leftwing.transform);
	btVector3 lw_offset(info.chassis_offset.x + info.chassis_size.x / 2.3f, info.chassis_offset.y + info.chassis_size.y / 2.5f, info.chassis_offset.z - info.chassis_size.z / 6.0f);
	lw_offset = lw_offset.rotate(q.getAxis(), q.getAngle());
	leftwing.transform.M[12] += lw_offset.getX();
	leftwing.transform.M[13] += lw_offset.getY();
	leftwing.transform.M[14] += lw_offset.getZ();
	leftwing.color = info.color;

	Cube visor(info.chassis_size.x / 1.15f, info.chassis_size.y*2, info.chassis_size.z / 100.0f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&visor.transform);
	btVector3 v_offset(info.chassis_offset.x, info.chassis_offset.y + info.chassis_size.y / 2.5f, info.chassis_offset.z + info.chassis_size.z / 8);
	v_offset = v_offset.rotate(q.getAxis(), q.getAngle());
	visor.transform.M[12] += v_offset.getX();
	visor.transform.M[13] += v_offset.getY();
	visor.transform.M[14] += v_offset.getZ();
	visor.color = { info.color.r-0.7f, info.color.g-0.65f, info.color.b-0.8f };

	Cube plate(info.chassis_size.x / 2.3f, info.chassis_size.y / 1.75f, info.chassis_size.z / 100.0f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&plate.transform);
	btVector3 p_offset(info.chassis_offset.x, info.chassis_offset.y - info.chassis_size.y / 5, info.chassis_offset.z - info.chassis_size.z / 2.0f);
	p_offset = p_offset.rotate(q.getAxis(), q.getAngle());
	plate.transform.M[12] += p_offset.getX();
	plate.transform.M[13] += p_offset.getY();
	plate.transform.M[14] += p_offset.getZ();
	plate.color = White;

	Cube seatf(info.chassis_size.x / 1.3f, info.chassis_size.y*1.6f, info.chassis_size.z / 100.0f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&seatf.transform);
	btVector3 sf_offset(info.chassis_offset.x, info.chassis_offset.y + info.chassis_size.y / 2.5f, info.chassis_offset.z - info.chassis_size.z / 16.0f);
	sf_offset = sf_offset.rotate(q.getAxis(), q.getAngle());
	seatf.transform.M[12] += sf_offset.getX();
	seatf.transform.M[13] += sf_offset.getY();
	seatf.transform.M[14] += sf_offset.getZ();
	seatf.color = Maroon;

	Cube seatb(info.chassis_size.x / 1.3f, info.chassis_size.y*1.6f, info.chassis_size.z / 100.0f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&seatb.transform);
	btVector3 sb_offset(info.chassis_offset.x, info.chassis_offset.y + info.chassis_size.y / 2.5f, info.chassis_offset.z - info.chassis_size.z / 4.0f);
	sb_offset = sb_offset.rotate(q.getAxis(), q.getAngle());
	seatb.transform.M[12] += sb_offset.getX();
	seatb.transform.M[13] += sb_offset.getY();
	seatb.transform.M[14] += sb_offset.getZ();
	seatb.color = Maroon;

	chassis.Render();
	driver.Render();
	line.Render();
	rightwing.Render();
	leftwing.Render();
	visor.Render();
	plate.Render();
	seatf.Render();
	seatb.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}

void PhysVehicle3D::Rotate(float angle)
{
	// Counter clock-wise rotation around the y axis

	float mat[16];
	memset(mat, 0.0f, sizeof(mat));

	// Position
	vec3 p = GetPos();
	mat[12] = p.x;
	mat[13] = p.y;
	mat[14] = p.z;
	mat[15] = 1;

	// Rotation
	mat[0] = cos(angle);
	mat[2] = -sin(angle);
	mat[5] = 1;
	mat[8] = sin(angle);
	mat[10] = cos(angle);

	SetTransform(mat);

}