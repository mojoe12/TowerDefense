#include "stdafx.h"
#include "Map.h"
#include "Terrain.h"
#include "Road.h"

class Cell;

namespace LogicLibrary
{
	Map::Map(int n, std::shared_ptr<Machine> mach)
	{
		cells = std::vector<std::vector<std::shared_ptr<Cell>>>(n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Coordinate<double> co(i, j);
				Road road(co, mach, true, true);
				Cell cell(i, j, std::make_shared<Road>(road));
				cells[i].push_back(std::make_shared<Cell>(cell));
			}
		}
	}


	Map::~Map()
	{
		// delete things
	}

	void Map::add(std::shared_ptr<MapObject> mo) {
		Coordinate<int> position = mo->getPosition();
		cells[position.X()][position.Y()]->addPtr(mo);
	}

	int Map::getHeight() const
	{
		return cells.size();
	}

	int Map::getWidth() const
	{
		return cells[0].size();
	}

	vec & Map::getContentsAt(int i, int j)
	{
		return (cells[i][j])->getContents();
	}

	const Terrain& Map::getTerrainAt(int i, int j) const
	{
		return cells[i][j]->getTerrain();
	}
}
