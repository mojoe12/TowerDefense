#include "stdafx.h"
#include "SimpleWave.h"
#include "Werewolf.h"
#include <vector>
#include <memory>
namespace LogicLibrary
{
	
	static const double startTime = 1;

	SimpleWave::SimpleWave(std::shared_ptr<Machine> machptr)
	{
		Werewolf ww(Coordinate<double>(0, 0), machptr);
		auto wwptr = std::shared_ptr<Attacker>(&ww);
		std::vector<pair> atkrs;
		atkrs.push_back(make_pair(startTime, wwptr));
		Wave(machptr, atkrs);
	}


	SimpleWave::~SimpleWave()
	{
	}
}
