#pragma once
#include <vector>
#include <memory>
#include "Coordinate.h"

namespace LogicLibrary
{

	class MapObject;
	class Terrain;
	using Vec = std::vector<std::shared_ptr<MapObject>>;

	// 

	class Cell
	{
	public:
		Cell(int, int, std::shared_ptr<Terrain>);
		~Cell();

		Vec& getContents();
		const Terrain& getTerrain() const;
		void addPtr(std::shared_ptr<MapObject>);
		void dltPtr(std::shared_ptr<MapObject>);

	private:
		Coordinate<int> mapIndex;
		Vec contents; // doesnt include terrain
		std::shared_ptr<Terrain> terrain;

	};


}