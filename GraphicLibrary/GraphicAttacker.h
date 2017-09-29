#pragma once
#include "AnimatedBitmapObject.h"
#include <memory>
#include "GraphicStorage.h"

namespace GraphicLibrary
{
	enum class Direction {
		Up,
		Right,
		Down,
		Left
	};

	enum class FootFirst {
		Left,
		Right
	};

	class GraphicAttacker :
		public AnimatedBitmapObject
	{
	public:
		GraphicAttacker();
		GraphicAttacker(int);
		~GraphicAttacker();
		void getState() override;
		void editBrush(int, int, int, int);
		Direction direction;
		FootFirst footFirst;
	private:
		int bitmapIndex;
	};

}