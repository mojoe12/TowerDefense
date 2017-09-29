#pragma once
#include <memory>
#include "Coordinate.h"

namespace LogicLibrary
{

	class Machine;

	class MapObject
	{
	public:
		MapObject();
		MapObject(Coordinate<double> pos, std::shared_ptr<Machine> machptri);
		~MapObject();
		virtual void Update(double time) = 0;
		Coordinate<double> getPosition() const;

	protected:
		std::shared_ptr<Machine> machptr;
		Coordinate<double> position;


		// some graphical representation

		// collisions:
		// interaction between graphics and library
		// one simple solution is to put everything in a bounding box
		// do all such interactions at the cell level maybe?

	};


}