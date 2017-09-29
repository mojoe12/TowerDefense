#include "stdafx.h"
#include "PathObject.h"


namespace LogicLibrary
{
	PathObject::PathObject()
	{
		currentIndex = 0;
	}

	PathObject::PathObject(std::vector<Coordinate<int>> posi)
	{
		positions = posi;
		currentIndex = 0;
	}


	PathObject::~PathObject()
	{
	}

	Coordinate<int> PathObject::getNext()
	{
		if (currentIndex >= positions.size()) 
		{
			return positions[positions.size() - 1];
		}
		return positions[currentIndex++];
	}
}