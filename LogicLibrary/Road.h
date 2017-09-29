#pragma once
#include "Terrain.h"
#include "GraphicTerrain.h"

namespace LogicLibrary
{
	class Road :
		public LogicLibrary::Terrain, protected GraphicLibrary::GraphicTerrain
	{
	public:
		Road(LogicLibrary::Coordinate<double>, std::shared_ptr<Machine>, bool, bool);
		~Road();

		void Update(double time);

		double getSpeed() const override;
		bool canBuild() const override;
		bool canWalk() const override;

	private:
		bool ifcanbuild;
		bool ifcanwalk;
	};


}