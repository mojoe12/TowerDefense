#include "stdafx.h"
#include "Road.h"

static const double speed = 1;
namespace LogicLibrary
{

	Road::Road(Coordinate<double> posi, std::shared_ptr<Machine> machptri, bool canwalk = true, bool canbuild = true) :
		Terrain(posi, machptri)
	{
		ifcanwalk = canwalk;
		ifcanbuild = canbuild;
	}

	Road::~Road()
	{
	}

	void Road::Update(double time)
	{
		Terrain::Update(time);
		GraphicTerrain::getState();
		//AnimatedBitmapObject::zoomIn(...);
	}

	double Road::getSpeed() const
	{
		return speed;
	}

	bool Road::canBuild() const
	{
		return ifcanbuild;
	}

	bool Road::canWalk() const
	{
		return ifcanwalk;
	}

}