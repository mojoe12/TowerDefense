#pragma once
#include "AnimatedBitmapObject.h"

namespace GraphicLibrary
{

	class GraphicTerrain :
		public AnimatedBitmapObject
	{
	public:
		GraphicTerrain();
		GraphicTerrain(int);
		~GraphicTerrain();
		void getState() override;

	private:
		int bitmapIndex;
	};
}