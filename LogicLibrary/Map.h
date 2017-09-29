#pragma once
#include <vector>
#include <memory>
#include "Cell.h"
#include "Machine.h"

namespace LogicLibrary
{

	class MapObject;
	class Terrain;

	using vec = std::vector<std::shared_ptr<MapObject>>;
	using cellmap = std::vector<std::vector<std::shared_ptr<Cell>>>;

	class Map
	{
	public:
		Map(int, std::shared_ptr<Machine>);
		~Map();

		void add(std::shared_ptr<MapObject>);
		int getHeight() const;
		int getWidth() const;
		vec& getContentsAt(int i, int j);
		const Terrain& getTerrainAt(int i, int j) const;

	private:
		cellmap cells;

	};

}