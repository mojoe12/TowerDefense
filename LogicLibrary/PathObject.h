#pragma once
#include <vector>
#include "Coordinate.h"

namespace LogicLibrary
{

	class PathObject
	{
	public:
		PathObject(); // needs to set currentindex to 0 initially
		PathObject(std::vector<Coordinate<int>>);
		~PathObject();
		Coordinate<int> getNext();

	private:
		int currentIndex;
		std::vector<Coordinate<int>> positions;
	};

	// map holds all paths
	// usually, map returns the same path
	// but after events or based on parameters
	// it can choose a different one
}