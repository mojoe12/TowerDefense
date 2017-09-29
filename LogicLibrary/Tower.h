#pragma once
#include "MapObject.h"
#include <memory>
#include <vector>

namespace LogicLibrary
{

	class Weapon;
	class Tower :
		public MapObject
	{
	public:
		Tower(Coordinate<double>, std::shared_ptr<Machine>, double);
		~Tower();
		virtual void Update(double time);
		void changePosition(Coordinate<double>);

	protected:
		virtual bool shouldCreateWeapon(double time);
		virtual std::shared_ptr<Weapon> createWeapon() = 0;
	private:
		std::vector<std::shared_ptr<Weapon>> weapon;
		double cooldown;
		double checkTime;
		bool multipleOk;
	};


	// i dont think map should have the control or the data of weapon
	// ok i changed that

	// crap i dont know whether map should hold weapon to draw it
	// or if tower should because it creates and controls it
	// if its the first, i could just keep a shared_ptr to it


}