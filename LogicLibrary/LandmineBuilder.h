#pragma once
#include "Tower.h"
#include "GraphicTower.h"

namespace LogicLibrary
{

	class LandmineBuilder :
		public Tower, protected GraphicLibrary::GraphicTower
	{

	public:
		LandmineBuilder(Coordinate<double>, std::shared_ptr<Machine> machptri);
		~LandmineBuilder();
		void Update(double time);

	protected:
		std::shared_ptr<Weapon> createWeapon() override;
	};


}