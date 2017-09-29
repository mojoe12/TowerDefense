#include "stdafx.h"
#include "Cell.h"
#include "Coordinate.h"
#include <algorithm>
#include "Terrain.h"

namespace LogicLibrary
{

	Cell::Cell(int x, int y, std::shared_ptr<Terrain> terr) :
		contents(std::vector<std::shared_ptr<MapObject>>()),
		mapIndex(Coordinate<int>(x, y)),
		terrain(terr)
	{
	}


	Cell::~Cell()
	{
	}

	Vec& Cell::getContents()
	{
		return contents;
	}

	const Terrain& Cell::getTerrain() const
	{
		return *terrain;
	}

	void Cell::addPtr(std::shared_ptr<MapObject> ptr)
	{
		contents.push_back(ptr);
	}

	void Cell::dltPtr(std::shared_ptr<MapObject> ptr)
	{
		std::vector<std::shared_ptr<MapObject>>::iterator it;
		it = find(contents.begin(), contents.end(), ptr);
		if (it != contents.end())
		{
			contents.erase(it);
		}
	}
}
