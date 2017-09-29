#include "stdafx.h"
#include "Tower.h"
#include "Weapon.h"

namespace LogicLibrary
{

	Tower::Tower(Coordinate<double> positioni, std::shared_ptr<Machine> machptri, double cooldowni) :
		MapObject(positioni, machptri),
		cooldown(cooldowni),
		checkTime(0),
		multipleOk(true)
	{
	}


	Tower::~Tower()
	{
		// delete weapons that still there
		// or if map doesnt do it without my help
	}

	void Tower::Update(double time)
	{
		for (size_t i = 0; i < weapon.size(); ++i) {
			if (weapon[i] == nullptr) {
				weapon.erase(weapon.begin() + i);
				--i;
			}
		}
		shouldCreateWeapon(time);
	}

	void Tower::changePosition(Coordinate<double> pos)
	{
		position = pos;
	}

	bool Tower::shouldCreateWeapon(double time)
	{
		bool shouldCreate = multipleOk || !weapon.size();
		if (shouldCreate && time >= checkTime)
		{
			checkTime += cooldown;
			weapon.push_back(createWeapon());
			return true;
		}
		return false;
	}

}