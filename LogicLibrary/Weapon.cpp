#include "stdafx.h"
#include "Weapon.h"
#include "Machine.h"
#include <memory>

namespace LogicLibrary
{

	Weapon::Weapon(Coordinate<double> posi, std::shared_ptr<Machine> machptri, Coordinate<double> velo) :
		MapObject(posi, machptri),
		velocity(velo),
		lastPosition(position),
		lastTime(0)
	{
	}

	Weapon::~Weapon()
	{
	}

	void Weapon::Update(double time)
	{
		// order?
		updatePosition(time);
		Trigger();
	}

	void Weapon::updatePosition(double time)
	{
		lastPosition = position;
		double timedelta = time - lastTime;
		Coordinate<double> positiondelta = Coordinate<double>(velocity.X() * timedelta, velocity.Y() * timedelta);
		position = Coordinate<double>(position.X() + positiondelta.X(), position.Y() + positiondelta.Y());
		lastTime = time;
	}

}