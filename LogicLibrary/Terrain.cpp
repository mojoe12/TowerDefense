#include "stdafx.h"
#include "Terrain.h"

namespace LogicLibrary
{

	Terrain::Terrain(Coordinate<double> positioni, std::shared_ptr<Machine> machptri) :
		MapObject(positioni, machptri)
	{
	}


	Terrain::~Terrain()
	{
	}

	void Terrain::Update(double time)
	{
		// if time is ..such and such..
		// then would i change to a diff. terrain?
		// maybe same terrain, diff. graphical rep.
		// that makes more sense
	}

}