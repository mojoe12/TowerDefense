#pragma once
#include "Weapon.h"
#include "GraphicWeapon.h"

namespace LogicLibrary
{

	class Landmine :
		public Weapon, protected GraphicLibrary::GraphicWeapon
	{
	public:
		Landmine(Coordinate<double>, std::shared_ptr<Machine>);
		~Landmine();

		void Update(double);

		void Trigger() override;
		bool ifTriggered() override;

	private:
		double damage;
	};


}