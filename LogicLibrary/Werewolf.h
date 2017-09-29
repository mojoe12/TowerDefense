#pragma once
#include "Attacker.h"
#include "GraphicAttacker.h"

namespace LogicLibrary
{
	class Werewolf :
		public Attacker, protected GraphicLibrary::GraphicAttacker
	{
	public:
		Werewolf(LogicLibrary::Coordinate<double>, std::shared_ptr<Machine>);
		~Werewolf();
		void Update(double);

	private:
		static const double normalSpeed;
		static const double initialHealth;
		static const int bitmapIndex;
	};


}