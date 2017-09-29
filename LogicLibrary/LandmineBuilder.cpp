#include "stdafx.h"
#include "LandmineBuilder.h"
#include "Landmine.h"
#include <memory>

static const double cooldown = 5;
namespace LogicLibrary
{

	LandmineBuilder::LandmineBuilder(Coordinate<double> positioni, std::shared_ptr<Machine> machptri) :
		Tower(positioni, machptri, ::cooldown)
	{
	}
	LandmineBuilder::~LandmineBuilder()
	{
	}

	void LandmineBuilder::Update(double time)
	{
		Tower::Update(time);
		GraphicTower::getState();
		//AnimatedBitmapObject::zoomIn();
	}

	std::shared_ptr<Weapon> LandmineBuilder::createWeapon()
	{
		Landmine wep (position, machptr); //?? hmm
		return std::shared_ptr<Landmine>(&wep);
	}

}