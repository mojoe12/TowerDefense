#include "stdafx.h"
#include "Machine.h"
#include <memory>

#include "Map.h"

namespace LogicLibrary
{
	Machine::Machine(int size, std::shared_ptr<GraphicLibrary::GraphicStorage> gsi)
	{
		gs = gsi;
	}


	Machine::~Machine()
	{
	}

	void Machine::Update(double time)
	{
		for (auto ter : terrains)
		{
			ter->Update(time);
		}
		for (auto atkr : attackers) {
			atkr->Update(time);
		}
		for (auto tow : towers) {
			tow->Update(time);
		}
		for (auto wep : weapons) {
			wep->Update(time);
		}
		// order?
	}

	void Machine::setMap(std::shared_ptr<Map> mapptr)
	{
		map = mapptr;
	}

	void Machine::setPaths(std::vector<std::shared_ptr<PathObject>> pathsi)
	{
		possiblePaths = pathsi;
	}

	void Machine::addAttacker(std::shared_ptr<Attacker> atkr)
	{
		attackers.push_back(atkr);
		map->add(atkr);
	}

	void Machine::dltAttacker(std::shared_ptr<Attacker> atkr)
	{
		std::vector<std::shared_ptr<Attacker>>::iterator it;
		it = find(attackers.begin(), attackers.end(), atkr);
		if (it != attackers.end())
		{
			attackers.erase(it);
		}
	}

	void Machine::addTower(std::shared_ptr<Tower> tow)
	{
		towers.push_back(tow);
	}

	void Machine::dltTower(std::shared_ptr<Tower> tow)
	{
		std::vector<std::shared_ptr<Tower>>::iterator it;
		it = find(towers.begin(), towers.end(), tow);
		if (it != towers.end())
		{
			towers.erase(it);
		}
	}

	void Machine::addWeapon(std::shared_ptr<Weapon> wep)
	{
		weapons.push_back(wep);
	}

	void Machine::dltWeapon(std::shared_ptr<Weapon> wep)
	{
		std::vector<std::shared_ptr<Weapon>>::iterator it;
		it = find(weapons.begin(), weapons.end(), wep);
		if (it != weapons.end())
		{
			weapons.erase(it);
		}
	}

	const Terrain& Machine::getTerrainAt(int i, int j) const
	{
		return map->getTerrainAt(i, j);
	}

	std::vector<std::shared_ptr<Attacker>> Machine::getAttackersAt(int i, int j) const
	{
		std::vector<std::shared_ptr<Attacker>> atkrs;
		for (auto mapobject : map->getContentsAt(i, j))
		{
			std::shared_ptr<Attacker> atkr = std::dynamic_pointer_cast<Attacker>(mapobject);
			if (atkr)
			{
				atkrs.push_back(atkr);
			}
		}
		return atkrs;
	}

	std::shared_ptr<PathObject> Machine::getPath(std::shared_ptr<Attacker> atkr) const
	{
		// something better here, no idea what
		// this will be a long-term change
		return possiblePaths[0];
	}
	std::shared_ptr<GraphicLibrary::GraphicStorage> Machine::getGS() const
	{
		return gs;
	}
}
