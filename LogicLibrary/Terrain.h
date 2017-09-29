#pragma once
#include "MapObject.h"

namespace LogicLibrary
{
	class Terrain :
		public MapObject
	{
	public:
		Terrain(Coordinate<double>, std::shared_ptr<Machine>);
		~Terrain();
		virtual void Update(double time);

		virtual bool canWalk() const = 0; // save memory this way
		virtual bool canBuild() const = 0;
		virtual double getSpeed() const = 0;

	private:

		// graphics

	};
}