#pragma once
#include "AnimatedBitmapObject.h"

namespace GraphicLibrary
{
	enum class BuildState {
		Building,
		Built,
		Destroyed
	};

	enum class FireState {
		Inactive,
		Firing
	};

	class GraphicTower :
		public AnimatedBitmapObject
	{
	public:
		GraphicTower();
		GraphicTower(int);
		~GraphicTower();
		void getState() override;
		BuildState buildState;
		FireState fireState;

	private:
		int bitmapIndex;
	};

}