#include "stdafx.h"
#include "Landmine.h"
#include "Machine.h"

namespace LogicLibrary
{
	static Coordinate<double> velo(0, 0);
	static double damageDealt = 10;

	Landmine::Landmine(Coordinate<double> positioni, std::shared_ptr<Machine> machptri) :
		Weapon(positioni, machptri, velo),
		damage(damageDealt)
	{
	}

	void Landmine::Update(double time)
	{
		Weapon::Update(time);
		GraphicWeapon::getState();
		//AnimatedBitmapObject::zoomIn(...);
	}

	void Landmine::Trigger()
	{
		if (!ifTriggered()) return;

		Coordinate<int> pos_int(position);
		for (auto atkr : machptr->getAttackersAt(pos_int.X(), pos_int.Y())) {
			atkr->loseHealth(damage);
		}
		machptr->dltWeapon(std::shared_ptr<Weapon>(this));
	}

	bool Landmine::ifTriggered()
	{
		Coordinate<int> pos_int(position);
		return machptr->getAttackersAt(pos_int.X(), pos_int.Y()).size() > 0;
	}

	Landmine::~Landmine()
	{
	}
}
