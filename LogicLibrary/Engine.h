#pragma once
#include "Machine.h"
#include "Wave.h"
#include "GraphicStorage.h"

namespace LogicLibrary
{
	using pair = std::pair<double, std::shared_ptr<Attacker>>;

	class Engine
	{
	public:
		Engine();
		Engine(std::shared_ptr<Machine>, std::shared_ptr<Wave>, double, double);
		~Engine();
		void Update();
		static void loadBrushSet(std::shared_ptr<GraphicLibrary::GraphicStorage>);
		void reportStatus() const;

		std::shared_ptr<Machine> getMachine();


	private:
		std::shared_ptr<Machine> mach;
		std::shared_ptr<Wave> wave;
		static std::shared_ptr<GraphicLibrary::GraphicStorage> brushSet; // static load method
		double time;
		double timeIncrement;
		const double ti0 = 0.1;

		double money;
		const double mi0 = 100;
		// other things for user interaction will go here in the future


		// engine creates the wave (checks it), and then tells the map to update
		// function arguments with reference to updating the map
	};

}