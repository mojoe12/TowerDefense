#pragma once
#include "BitmapObject.h"
#include "D2d1.h"

namespace GraphicLibrary
{

	class AnimatedBitmapObject :
		public GraphicObject
	{
	public:
		AnimatedBitmapObject();
		~AnimatedBitmapObject();
		virtual void getState() = 0;

	protected:
		void zoomIn(ID2D1BitmapBrush*, int, int, int, int, int, int, int, int);
		// put in #includes for IBB
		// might need cell-to-pixels ratio
		// other problems? hmm

	};
}