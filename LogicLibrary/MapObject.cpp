#include "stdafx.h"
#include "MapObject.h"

namespace LogicLibrary
{

	MapObject::MapObject()
	{

	}

	MapObject::MapObject(Coordinate<double> pos, std::shared_ptr<Machine> machptri)
	{
		position = Coordinate<double>(pos.X(), pos.Y());
		machptr = machptri;
	}

	MapObject::~MapObject()
	{
	}

	Coordinate<double> MapObject::getPosition() const
	{
		return position;
	}

}