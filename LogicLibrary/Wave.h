#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "Machine.h"

namespace LogicLibrary
{

	class Attacker;

	// need another class that sets the engine going
	// calls the engine to run

	// wave should be an abstract class
	// derive from it a naive class

	using pair = std::pair<double, std::shared_ptr<Attacker>>;
	// time to add, attacker info

	class Wave
	{
	public:
		Wave();
		Wave(std::shared_ptr<Machine>, std::vector<pair>);
		~Wave();
		void Update(double time);

	private:
		std::shared_ptr<Machine> machine;
		std::vector<pair> createInfo;
		int infoIndex;
	};
}