#pragma once
#include <vector>
#include <memory>
// turn these two header files

//#include "Map.h"
#include "Terrain.h"
#include "Attacker.h"
#include "Tower.h"
#include "Weapon.h"
#include <algorithm>
#include "GraphicStorage.h"

namespace LogicLibrary
{
	class PathObject;
	class Map;

	using vec = std::vector<std::shared_ptr<MapObject>>;
	class Machine
	{
	public:
		Machine() {}
		Machine(int, std::shared_ptr<GraphicLibrary::GraphicStorage>);
		~Machine();
		void Update(double time); // calls everything

		void setMap(std::shared_ptr<LogicLibrary::Map>);
		void setPaths(std::vector<std::shared_ptr<PathObject>>);

		void addAttacker(std::shared_ptr<Attacker>);
		void dltAttacker(std::shared_ptr<Attacker>);

		void addTower(std::shared_ptr<Tower>);
		void dltTower(std::shared_ptr<Tower>);

		void addWeapon(std::shared_ptr<Weapon>);
		void dltWeapon(std::shared_ptr<Weapon>);

		const Terrain& getTerrainAt(int i, int j) const;
		std::vector<std::shared_ptr<Attacker>> getAttackersAt(int i, int j) const;
		std::shared_ptr<PathObject> getPath(std::shared_ptr<Attacker>) const;
		std::shared_ptr<GraphicLibrary::GraphicStorage> getGS() const;


	private:

		std::shared_ptr<Map> map;

		std::vector<std::shared_ptr<PathObject>> possiblePaths;

		std::shared_ptr<GraphicLibrary::GraphicStorage> gs; //kloodge

		std::vector<std::shared_ptr<Terrain>> terrains; // in order of size
		std::vector<std::shared_ptr<Attacker>> attackers;
		std::vector<std::shared_ptr<Tower>> towers;
		std::vector<std::shared_ptr<Weapon>> weapons;
	};


}