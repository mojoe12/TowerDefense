#pragma once
#include "Wave.h"

namespace LogicLibrary
{
	class SimpleWave :
		public Wave
	{
	public:
		SimpleWave(std::shared_ptr<Machine>);
		~SimpleWave();
	};


}